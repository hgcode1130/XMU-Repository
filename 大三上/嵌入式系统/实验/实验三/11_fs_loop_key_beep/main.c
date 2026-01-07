#include "fs3399_gpio.h"
#include "fs3399_timer.h"


// 宏定义，用于操作蜂鸣器引脚
#define BEEP_PIN_BIT (0x1 << 23)
#define BEEP_GPIO_DDR (GPIO1->SWPORTA_DDR) // 方向寄存器
#define BEEP_GPIO_DR (GPIO1->SWPORTA_DR)   // 数据寄存器

// 宏定义，用于读取KEY1引脚 (GPIO1_B2, 也就是第10位)
#define KEY1_PIN_BIT (0x1 << 10)
#define KEY1_GPIO_EXT (GPIO1->EXT_PORTA) // 外部端口寄存器，用于读取引脚状态

int main() {
  // 定义一个标志位来记录蜂鸣器的当前状态，0代表关，1代表开
  int buzzer_state = 0;

  // 1. 设置 KEY1 (GPIO1_B2) 为输入模式 (对应位清零)
  GPIO1->SWPORTA_DDR &= ~KEY1_PIN_BIT;

  // 2. 设置 蜂鸣器 (GPIO1_C7) 为输出模式 (对应位置位)
  BEEP_GPIO_DDR |= BEEP_PIN_BIT;

  // --- 主循环 ---
  while (1) {
    if (0 == (KEY1_GPIO_EXT & KEY1_PIN_BIT)) {
      fs_delay_ms(10);
      if (0 == (KEY1_GPIO_EXT & KEY1_PIN_BIT)) {
        if (buzzer_state == 0) {
          BEEP_GPIO_DR |= BEEP_PIN_BIT;
          buzzer_state = 1;
        } else {
          BEEP_GPIO_DR &= ~BEEP_PIN_BIT;
          buzzer_state = 0;
        }

        while (0 == (KEY1_GPIO_EXT & KEY1_PIN_BIT))
          ;
      }
    }
  }

  return 0;
}