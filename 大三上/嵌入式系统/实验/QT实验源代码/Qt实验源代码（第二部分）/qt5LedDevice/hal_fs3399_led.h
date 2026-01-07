#ifndef HAL_FS3399_LED_H
#define HAL_FS3399_LED_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

// 初始化LED设备
extern int led_init();

// 打开特定编号的LED
extern int led_on(int nr);

// 关闭特定编号的LED
extern int led_off(int nr);

extern int led_close();

enum Leds{
    LED1,
    LED2,
    LED3
};

//LED操作
#define LED1_ON    _IO('x',1)
#define LED1_OFF   _IO('x',0)
#define LED2_ON    _IO('z',1)
#define LED2_OFF   _IO('z',0)
#define LED3_ON    _IO('y',1)
#define LED3_OFF   _IO('y',0)

// LED路径定义
#define LED_PATH "/dev/leds_ctl"

#endif // HAL_S5P6818_LED_H
