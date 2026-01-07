
#include "main.h"
#include "stdio.h"
#include "i2c.h"       
#include "usart.h"     
#include "gpio.h"    
#include "LM75A.h"   
#include "zlg72128.h"


#define ZLG72128_I2C_ADDR           0x60


#define DECIMAL_POINT_POSITION      1

// ZLG72128 8个数码管的写地址（从左到右）
static const uint8_t ZLG_DISPLAY_ADDRESSES[8] = {
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
};

// 7段数码管共阴极编码查找表 (0-9)
static const uint8_t SEVEN_SEG_MAP_NORMAL[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
// 带小数点的7段数码管编码查找表 (0-9)
static const uint8_t SEVEN_SEG_MAP_DOT[10] = {
    0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF
};


static void SystemClock_Config(void);
static void Calculate_TemperatureDigits(uint16_t raw_temp, uint8_t* digits);
static void Display_Update(const uint8_t* digits, int8_t decimal_pos);
static inline uint8_t get_seg_code(uint8_t digit, uint8_t is_dot);


int main(void)
{
  uint16_t raw_temp_value;

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  LM75SetMode(CONF_ADDR, NORMOR_MODE);

  while (1)
  {

    raw_temp_value = LM75GetTempReg();

    if (raw_temp_value != EVL_ER) 
    {
      uint8_t display_digits[8] = {0}; 

      Calculate_TemperatureDigits(raw_temp_value, display_digits);

      Display_Update(display_digits, DECIMAL_POINT_POSITION);
    }
    
    HAL_Delay(1000);
  }
}


static void Calculate_TemperatureDigits(uint16_t raw_temp, uint8_t* digits)
{
    uint32_t temp_scaled = (uint32_t)raw_temp * 125000;
    
    // 从右到左（从最低位到最高位）依次提取每一位数字
    for (int i = 7; i >= 0; i--)
    {
        digits[i] = temp_scaled % 10;
        temp_scaled /= 10;
    }
}

static void Display_Update(const uint8_t* digits, int8_t decimal_pos)
{
    uint8_t tx_byte; // 用于I2C发送的单字节缓冲区

    // 循环遍历8个数码管
    for (int i = 0; i < 8; i++)
    {
        uint8_t current_digit = digits[i];
        uint8_t needs_dot = (i == decimal_pos);
        
        // 从查找表获取对应的7段码
        tx_byte = get_seg_code(current_digit, needs_dot);
        
        // 通过I2C将7段码写入ZLG72128对应的显示地址
        I2C_ZLG72128_Write_char(&hi2c1, ZLG72128_I2C_ADDR, ZLG_DISPLAY_ADDRESSES[i], &tx_byte);
    }
}

static inline uint8_t get_seg_code(uint8_t digit, uint8_t is_dot)
{
    if (digit > 9) {
        return 0x00; // 对于无效数字，显示空白
    }
    
    return is_dot ? SEVEN_SEG_MAP_DOT[digit] : SEVEN_SEG_MAP_NORMAL[digit];
}


static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
    // 可以在此添加LED闪烁等错误指示代码
  }
}