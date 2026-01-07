#ifndef BEEPDEVICE_H  // 防止头文件重复包含
#define BEEPDEVICE_H

#include <QObject>  // 包含 QObject 类的定义
#include <QDebug>  // 包含 Qt 调试输出的功能
#include <stdio.h>  // 标准输入输出库
#include <fcntl.h>  // 文件控制定义
#include <unistd.h>  // 提供对 POSIX 操作系统 API 的访问
#include <stdlib.h>  // 标准库定义
#include <sys/ioctl.h>  // 定义 ioctl() 系统调用

#define IOCTL_MAGIC 'B'  // 定义 IOCTL 的魔数
#define BEEP_ON _IO(IOCTL_MAGIC,  1)  // 定义打开蜂鸣器的命令
#define BEEP_OFF _IO(IOCTL_MAGIC, 0)  // 定义关闭蜂鸣器的命令
#define SET_FREQUENCY _IOW(IOCTL_MAGIC, 2, int)  // 定义设置蜂鸣器频率的命令

// 蜂鸣器设备类
class beepDevice : public QObject
{
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    explicit beepDevice(QObject *parent = nullptr);  // 构造函数
    void openBeepDevice();  // 打开蜂鸣器设备
    void changeBeepState(int state);  // 改变蜂鸣器状态
    void closeBeepFd();  // 关闭蜂鸣器设备文件描述符

private:
    int beepfd = 0;  // 蜂鸣器设备的文件描述符
};

#endif // BEEPDEVICE_H  // 结束头文件包含保护
