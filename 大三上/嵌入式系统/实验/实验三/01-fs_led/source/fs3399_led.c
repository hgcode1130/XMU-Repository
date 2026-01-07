#include "fs3399_led.h"

int FsLedInit() {
  GPIO4->SWPORTA_DDR |= (0x1 << 22); // LED1输出模式——GPIO4的DR的C6置1
  GPIO0->SWPORTA_DDR |= (0x1 << 2); // LED2输出模式——GPIO0的DR的A2置1
  GPIO0->SWPORTA_DDR |= (0x1 << 12); // LED3输出模式——GPIO0的DR的B4置1

  return 0;
}

int FsLedOn(int n) {
  switch (n) {
  case 1:
    GPIO4->SWPORTA_DR |= (0x1 << 22); // LED1灯亮——GPIO4的DR的C6置1
    return 0;
  case 2:
    GPIO0->SWPORTA_DR |= (0x1 << 2); // LED2灯亮——GPIO0的DR的A2置1
    return 0;
  case 3:
    GPIO0->SWPORTA_DR |= (0x1 << 12); // LED3灯亮——GPIO0的DR的B4置1
    return 0;
  defaule:
    return 0;
  }
}

int FsLedOff(int n) {
  switch (n) {
  case 1:
    GPIO4->SWPORTA_DR &= ~(0x1 << 22); // LED1灯灭——GPIO4的DR的C6置0
    return 0;
  case 2:
    GPIO0->SWPORTA_DR &= ~(0x1 << 2); // LED2灯灭——GPIO0的DR的A2置0
    return 0;
  case 3:
    GPIO0->SWPORTA_DR &= ~(0x1 << 12); // LED3灯灭——GPIO0的DR的B4置0
    return 0;
  defaule:
    return 0;
  }
}