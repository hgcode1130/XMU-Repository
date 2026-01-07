#include "hal_fs3399_beep.h"

int fd;  // 文件描述符，用于蜂鸣器文件操作

// 打开蜂鸣器节点
int beep_init()
{
    fd = open(BEEP_PATH, O_RDWR);  // 打开蜂鸣器文件
    if (fd < 0) {
        perror("open beep failed");  // 打开文件失败处理
    }
    return 0;
}


// 给蜂鸣器设置固定频率和占空比
int beep_on()
{
    return ioctl(fd,BEEP_ON);
}


// 给蜂鸣器设置频率和占空比为0，使其关闭声音
int beep_off()
{
    return ioctl(fd,BEEP_OFF);
}


// 关闭蜂鸣器文件
void beep_close()
{
    close(fd);  // 关闭文件描述符
}
