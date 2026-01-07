/**
 *
 * - 按键 "1": 电机顺时针旋转
 * - 按键 "2": 电机逆时针旋转
 * - 其他任意键: 电机停止
 *
 ******************************************************************************
 */

#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "stdio.h"
#include "usart.h"
#include "zlg72128.h" 
//================================================================================

// ZLG72128 I2C 寄存器地址
#define ZLG_KEY_VALUE_REG      0x01 // 普通键值寄存器
#define ZLG_FUNC_KEY_VALUE_REG 0x03 // 功能键寄存器

// 步进电机相关的GPIO定义
#define MOTOR_A_PORT GPIOD
#define MOTOR_A_PIN  GPIO_PIN_12
#define MOTOR_B_PORT GPIOH
#define MOTOR_B_PIN  GPIO_PIN_13
#define MOTOR_C_PORT GPIOE
#define MOTOR_C_PIN  GPIO_PIN_4
#define MOTOR_D_PORT GPIOG
#define MOTOR_D_PIN  GPIO_PIN_1

// 定义电机转速，数值越小，速度越快
#define MOTOR_STEP_DELAY 1

typedef enum {
    MOTOR_STOP = 0,             // 停止
    MOTOR_CLOCKWISE = 1,        // 顺时针
    MOTOR_COUNTERCLOCKWISE = 2  // 逆时针
} MotorState;

// 步进电机八拍驱动模式的GPIO状态表 (A, B, C, D相)
// 1 = GPIO_PIN_SET (高电平), 0 = GPIO_PIN_RESET (低电平)
const uint8_t step_patterns[8][4] = {
    {1, 0, 0, 0}, // 步 0: A
    {1, 1, 0, 0}, // 步 1: AB
    {0, 1, 0, 0}, // 步 2: B
    {0, 1, 1, 0}, // 步 3: BC
    {0, 0, 1, 0}, // 步 4: C
    {0, 0, 1, 1}, // 步 5: CD
    {0, 0, 0, 1}, // 步 6: D
    {1, 0, 0, 1}  // 步 7: DA
};

volatile MotorState g_motor_state = MOTOR_STOP;

extern I2C_HandleTypeDef hi2c1;


void SystemClock_Config(void);
static void Motor_SetStep(uint8_t step);
static void Motor_Rotate(MotorState direction, uint32_t delay_ms);
static void Handle_KeyPress(void);


int main(void) {
    // HAL库初始化，必须是第一个调用的函数
    HAL_Init();

    // 配置系统时钟
    SystemClock_Config();

    // 初始化由STM32CubeMX生成的各个外设
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    // 主循环
    while (1) {
        // 1. 处理按键输入，并根据按键更新电机状态
        Handle_KeyPress();

        // 2. 根据电机当前状态执行相应动作
        //    如果状态是STOP，则不执行任何操作，电机保持静止
        if (g_motor_state != MOTOR_STOP) {
            Motor_Rotate(g_motor_state, MOTOR_STEP_DELAY);
        }
    }
}


static void Motor_SetStep(uint8_t step) {
    // 参数范围检查
    if (step > 7) return;

    // 根据步数表设置四个GPIO的电平
    HAL_GPIO_WritePin(MOTOR_A_PORT, MOTOR_A_PIN, (GPIO_PinState)step_patterns[step][0]);
    HAL_GPIO_WritePin(MOTOR_B_PORT, MOTOR_B_PIN, (GPIO_PinState)step_patterns[step][1]);
    HAL_GPIO_WritePin(MOTOR_C_PORT, MOTOR_C_PIN, (GPIO_PinState)step_patterns[step][2]);
    HAL_GPIO_WritePin(MOTOR_D_PORT, MOTOR_D_PIN, (GPIO_PinState)step_patterns[step][3]);
}


static void Motor_Rotate(MotorState direction, uint32_t delay_ms) {
    if (direction == MOTOR_CLOCKWISE) {
        // 顺时针旋转 (步 0 -> 7)
        for (int i = 0; i < 8; i++) {
            Motor_SetStep(i);
            HAL_Delay(delay_ms);
        }
    } else if (direction == MOTOR_COUNTERCLOCKWISE) {
        // 逆时针旋转 (步 7 -> 0)
        for (int i = 7; i >= 0; i--) {
            Motor_SetStep(i);
            HAL_Delay(delay_ms);
        }
    }
}


static void Handle_KeyPress(void) {
    uint8_t key_value = 0x00;
    uint8_t func_key_value = 0xFF;

    // 从I2C设备读取普通键和功能键的键值
    I2C_ZLG72128_Read(&hi2c1, 0x61, ZLG_KEY_VALUE_REG, &key_value, 1);
    I2C_ZLG72128_Read(&hi2c1, 0x61, ZLG_FUNC_KEY_VALUE_REG, &func_key_value, 1);

    // 检查是否有任何按键被按下
    if (key_value != 0x00 || func_key_value != 0xFF) {
        // 假设按键 "1" 返回的键值是 0x01
        if (key_value == 0x01) {
            g_motor_state = MOTOR_CLOCKWISE;
        }
        // 假设按键 "2" 返回的键值是 0x02
        else if (key_value == 0x02) {
            g_motor_state = MOTOR_COUNTERCLOCKWISE;
        }
        // 其他任何按键都使电机停止
        else {
            g_motor_state = MOTOR_STOP;
        }
    }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 使能电源控制时钟 */
  __HAL_RCC_PWR_CLK_ENABLE();
  /* 配置电压调节器输出电压 */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* 初始化RCC振荡器 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; // 使用外部高速时钟
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                   // 打开HSE
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;               // 打开PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;       // PLL时钟源为HSE
  RCC_OscInitStruct.PLL.PLLM = 8;                            // HSE分频系数
  RCC_OscInitStruct.PLL.PLLN = 336;                          // PLL倍频系数
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                // 系统时钟分频系数
  RCC_OscInitStruct.PLL.PLLQ = 7;                            // USB/SDIO等时钟分频系数

  /* 初始化CPU, AHB和APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // 系统时钟源为PLL
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        // AHB不分频
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;         // APB1 4分频
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;         // APB2 2分频
}
