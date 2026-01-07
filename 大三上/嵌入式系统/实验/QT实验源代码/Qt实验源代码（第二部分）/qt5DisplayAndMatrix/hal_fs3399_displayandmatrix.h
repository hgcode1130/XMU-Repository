#ifndef HAL_FS3399_DISPLAYANDMATRIX_H  // 防止头文件重复包含
#define HAL_FS3399_DISPLAYANDMATRIX_H

#include <stdio.h>  // 包含标准输入输出库
#include <stdlib.h>  // 包含标准库，用于内存分配、程序控制等
#include <unistd.h>  // 提供对POSIX操作系统API的访问
#include <fcntl.h>  // 文件控制，用于处理文件描述符
#include <sys/types.h>  // 提供数据类型，如pid_t
#include <linux/input.h>  // Linux输入设备接口
#include <string.h>  // 提供字符串处理函数

// 外部声明，这些函数由设备驱动实现，用于初始化、运行、更新缓冲区和关闭设备
extern int dis_mat_init();  // 初始化显示和矩阵硬件
extern int Run();  // 运行设备，获取当前状态或值
extern void turn_new_buf(char value);  // 更新设备的缓冲区
extern void close_dis();  // 关闭设备

extern int fd;  // 文件描述符，通常用于设备文件的访问
extern char value;  // 用于存储从设备获取的值

// 定义 IOCTL 命令，这些是自定义的命令代码，用于与设备驱动程序进行特定的通信
#define SET_VAL _IO('Z', 0)  // 设置设备的值
#define GET_KEY _IO('Z', 1)  // 从设备获取某个键的状态或值

#endif  // HAL_S5P6818_DISPLAYANDMATRIX_H
