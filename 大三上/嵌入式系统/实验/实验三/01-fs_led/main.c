#include "fs3399_timer.h"
#include "fs3399_led.h"


int main() {
  // 设置LED1(GPIO4_C6)、LED2(GPIO0_A2)、LED3(GPIO0_B4)为输出模式
  FsLedInit();

  for (;;) {
    // 打开LED1
    FsLedOn(1);

    // 延时100ms
    fs_delay_ms(100);

    // 关闭LED1
    FsLedOff(1);

    // 延时100ms
    fs_delay_ms(100);

    // 打开LED2
    FsLedOn(2);

    // 延时100ms
    fs_delay_ms(100);

    // 关闭LED2
    FsLedOff(2);

    // 延时100ms
    fs_delay_ms(100);

    // 打开LED3
    FsLedOn(3);

    // 延时100ms
    fs_delay_ms(100);

    // 关闭LED3
    FsLedOff(3);

    // 延时100ms
    fs_delay_ms(100);
  }

  while (1) {
  }

  return 0;
}