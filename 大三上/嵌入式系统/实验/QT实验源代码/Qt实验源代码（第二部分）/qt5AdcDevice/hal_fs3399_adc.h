 #ifndef HAL_FS3399_ADC_H
#define HAL_FS3399_ADC_H

#include <stdio.h>    // 标准输入输出库
#include <fcntl.h>    // 文件控制库
#include <errno.h>    // 错误号定义
#include <unistd.h>   // UNIX标准函数定义
#include <linux/input.h>  // Linux输入设备接口
#include <sys/ioctl.h>    // 设备控制系统调用
#include <stdint.h>   // 标准整数类型
#include <string.h>   // 字符串处理
#include <stdlib.h>   // 标准库
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


// ADC初始化函数
extern int adc_init();

// 启动ADC并返回结果的函数
extern int Run();

// 读取系统文件系统中整数值的函数
extern int read_sysfs_int(int val);

// 关闭ADC设备
extern int adc_close();

// 当前电压值
extern int voltage;

#endif
