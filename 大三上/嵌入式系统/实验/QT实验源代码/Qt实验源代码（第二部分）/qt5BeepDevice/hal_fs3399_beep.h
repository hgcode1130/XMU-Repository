#ifndef HAL_FS3399_BEEP_H
#define HAL_FS3399_BEEP_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

// 蜂鸣器相关函数声明
extern int beep_init();  // 初始化蜂鸣器
extern int beep_on();  // 打开蜂鸣器
extern int beep_off();  // 关闭蜂鸣器
extern void beep_close();  // 关闭蜂鸣器

// 蜂鸣器设备文件路径
#define BEEP_PATH "/dev/buzzer_ctl"
#define BEEP_ON 1
#define BEEP_OFF 0

#endif // HAL_FS3399_BEEP_H
