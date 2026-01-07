#ifndef DCDEVICE_H  // 防止头文件重复包含
#define DCDEVICE_H

#include <QObject>  // 包含 QObject 类的定义
#include <stdio.h>  // 标准输入输出库
#include <fcntl.h>  // 文件控制定义
#include <unistd.h>  // 提供对 POSIX 操作系统 API 的访问
#include <stdlib.h>  // 标准库定义
#include <sys/ioctl.h>  // 定义 ioctl() 系统调用
#include <QDebug>  // 包含 Qt 调试输出的功能

#define IOCTL_MAGICDC 'D'  // 定义直流电机的 IOCTL 魔数
#define DC_MOTOR_ON _IO(IOCTL_MAGICDC, 0)  // 定义打开直流电机的命令
#define DC_MOTOR_OFF _IO(IOCTL_MAGICDC, 1)  // 定义关闭直流电机的命令
#define DC_MOTOR_DIR _IOW(IOCTL_MAGICDC, 2, int)  // 定义设置直流电机方向的命令

// 直流电机设备类，继承自 QObject
class dcDevice : public QObject
{
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    dcDevice();  // 构造函数
    void initDc();  // 初始化直流电机
    void controlDc(int operation);  // 控制直流电机的操作
    void closeDc();  // 关闭直流电机
    ~dcDevice();  // 析构函数

private:
    int dcfd = 0;  // 直流电机的文件描述符
};

#endif // DCDEVICE_H  // 结束头文件包含保护
