#ifndef HAL_FS3399_KEY_H
#define HAL_FS3399_KEY_H

#include <unistd.h>  // 引入UNIX标准函数定义
#include <sys/ioctl.h>  // 控制设备的系统调用
#include <sys/types.h>  // 基本系统数据类型
#include <sys/stat.h>  // 文件状态
#include <fcntl.h>  // 文件控制
#include <stdio.h>  // 标准输入输出库
#include <errno.h>  // 错误编号定义
#include <string.h>  // 字符串处理
#include <linux/input.h>  // Linux输入设备接口

#define KEYS_PATH "/dev/farsight_keys"

enum keyStae{
    KEY1_ON,
    KEY1_OFF,
    KEY2_ON,
    KEY2_OFF
};

// 初始化按键设备
extern void key_init();

extern int get_keys_clicked();
// 关闭按键设备
extern int key_close();
// 文件描述符，用于操作具体的设备文件
extern int fd;

#endif
