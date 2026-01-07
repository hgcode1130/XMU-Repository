#ifndef HAL_FS3399_KEY_H 
#define HAL_FS3399_KEY_H 

#include <unistd.h>  
#include <sys/ioctl.h>
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdio.h>  
#include <errno.h>  
#include <string.h>  
#include <linux/input.h>  
#include <stdlib.h>  

#define KEYS_PATH "/dev/farsight_keys" 

// 键盘按键状态
enum keyStae {
    KEY1_ON, // 按键1被按下
    KEY1_OFF, // 按键1被释放
    KEY2_ON, // 按键2被按下
    KEY2_OFF  // 按键2被释放
};

extern void key_init(); // 初始化键盘设备
extern int get_keys_clicked(); // 获取被按下的按键
extern int key_close(); // 关闭键盘设备
extern int fd; // 键盘设备的文件描述符

extern int led_init(); // 初始化LED设备
extern int led_on(int nr); // 打开指定编号的LED
extern int led_off(int nr); // 关闭指定编号的LED
extern int led_close(); // 关闭LED设备

// LED编号
enum Leds {
    LED1, // LED1编号
    LED2, // LED2编号
    LED3  // LED3编号
};

// 定义LED控制的ioctl命令
#define LED1_ON    _IO('x',1) // 打开LED1
#define LED1_OFF   _IO('x',0) // 关闭LED1
#define LED2_ON    _IO('z',1) // 打开LED2
#define LED2_OFF   _IO('z',0) // 关闭LED2
#define LED3_ON    _IO('y',1) // 打开LED3
#define LED3_OFF   _IO('y',0) // 关闭LED3

#define LED_PATH "/dev/leds_ctl" // LED设备文件路径

#endif // 结束头文件保护