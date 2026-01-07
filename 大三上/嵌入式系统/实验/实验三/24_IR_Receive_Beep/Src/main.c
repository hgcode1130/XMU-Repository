#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "RemoteInfrared.h"
// 定义LED所连接的GPIO端口和引脚
#define LED_PORT   GPIOG
#define LED_PIN    GPIO_PIN_6
// 定义需要响应的红外按键码
#define IR_TARGET_KEYCODE 8

#define LED_PULSE_DELAY_MS 5

__IO uint32_t GlobalTimingDelay100us; 

void SystemClock_Config(void);

static void Pulse_LED(void);


int main(void)
{
    uint8_t irKeyCode = 0; 

    // 系统和外设初始化
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    // 通过串口打印启动信息
    printf("\r\n>> FS-STM32 IR Receiver Demo <<\r\n");

    while (1)
    {
        // 等待并解码来自红外遥控器的按键信号
        irKeyCode = Remote_Infrared_KeyDeCode(); 

        // 检查接收到的键码是否为我们想要的目标按键
        if (irKeyCode == IR_TARGET_KEYCODE)
        {
            // 如果是目标按键，则驱动LED产生一个脉冲信号
            Pulse_LED();
        }
    }
}

static void Pulse_LED(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);   // 点亮LED
    HAL_Delay(LED_PULSE_DELAY_MS);                        // 保持点亮状态
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // 熄灭LED
    HAL_Delay(LED_PULSE_DELAY_MS);                        // 保持熄灭状态，完成一个脉冲周期
}