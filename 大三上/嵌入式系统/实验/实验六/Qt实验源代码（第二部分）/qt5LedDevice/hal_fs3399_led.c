#include "hal_fs3399_led.h"
int fd = 0;
int led_init()
{
   fd = 0;
   fd = open(LED_PATH, O_RDWR);
    if(fd < 0){
        perror("open led failed");
        return -1;
    }
    ioctl(fd,LED1_OFF);
    ioctl(fd,LED2_OFF);
    ioctl(fd,LED3_OFF);
    return 0;
}

// 打开指定编号的LED灯
int led_on(int nr)
{

    // 控制LED
    switch (nr) {
    case LED1:
        ioctl(fd,LED1_ON);
        break;
    case LED2:
        ioctl(fd,LED2_ON);
        break;
    case LED3:
        ioctl(fd,LED3_ON);
        break;
    default:
        break;
    }
    return 0;
}

// 关闭指定编号的LED灯
int led_off(int nr)
{
    int fd = open(LED_PATH, O_RDWR);
    if (fd < 0) {
        perror("open failed");
        return -1;
    }

    // 控制LED
    switch (nr) {
    case LED1:
        ioctl(fd,LED1_OFF);
        break;
    case LED2:
        ioctl(fd,LED2_OFF);
        break;
    case LED3:
        ioctl(fd,LED3_OFF);
        break;
    default:
        break;
    }
    return 0;
}


int led_close()
{
    return close(fd);
}
