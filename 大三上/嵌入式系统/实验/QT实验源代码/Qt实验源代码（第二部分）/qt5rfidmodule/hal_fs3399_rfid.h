#ifndef HAL_FS3399_RFID_H  // 防止头文件重复包含
#define HAL_FS3399_RFID_H

#include <stdio.h>       // 标准输入输出库
#include <string.h>      // 字符串处理库
#include <stdlib.h>      // 标准库，包含内存管理、随机数生成、排序和其他通用函数
#include <iconv.h>       // 包含用于字符编码转换的 iconv 函数
#include <sys/ioctl.h>   // 用于设备控制的 IOCTL 函数
#include <fcntl.h>       // 文件控制选项
#include <unistd.h>      // 访问 POSIX 操作系统 API
#include <sys/types.h>   // 定义数据类型，如 ssize_t
#include <sys/stat.h>    // 定义返回文件状态的结构和常量
#include <errno.h>       // 提供错误码

// 全局文件描述符，用于访问不同类型的 RFID 设备
extern int fd_hf;        // 高频（HF）RFID 设备的文件描述符
extern int fd_lf;        // 低频（LF）RFID 设备的文件描述符
extern int fd_nfc;       // 近场通信（NFC）RFID 设备的文件描述符
extern int fd_2_4G;      // 2.4G RFID 设备的文件描述符
extern int fd_915m;      // 915M RFID 设备的文件描述符
extern char* rfid_card;

// 函数声明
extern int init_rfid(int rfid);      // 初始化 RFID 设备
extern int close_rfid();     // 关闭 RFID 设备
extern char *read_hf();      // 读取高频（HF）RFID 标签数据
extern char *read_lf();      // 读取低频（LF）RFID 标签数据
extern char *read_nfc();     // 读取近场通信（NFC）RFID 标签数据
extern char *read_2_4G();    // 读取 2.4G RFID 标签数据
extern char *read_915m();    // 读取 915M RFID 标签数据
enum RFID {
    F13_56M,
    F125K,
    F915M,
    FNFC,
    F2_4G
};

#endif  // 结束条件编译块

