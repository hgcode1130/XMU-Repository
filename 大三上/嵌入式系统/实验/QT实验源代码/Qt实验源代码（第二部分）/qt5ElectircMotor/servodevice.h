#ifndef SERVODEVICE_H  // 预处理指令，防止头文件被多次包含
#define SERVODEVICE_H

#include <QObject>  // 包含 Qt 的对象模型基类
#include <stdio.h>  // 标准输入输出头文件
#include <fcntl.h>  // 文件控制头文件
#include <unistd.h>  // Unix 标准函数定义头文件
#include <stdlib.h>  // 标准库头文件
#include <sys/ioctl.h>  // 输入输出控制系统调用头文件
#include <QDebug>  // Qt 调试输出头文件

#define IOCTL_MAGICSERVO 'S'  // 定义 IOCTL 控制码
#define SET_ANGLE _IO(IOCTL_MAGICSERVO, 6)  // 定义设置舵机角度的控制码

class servoDevice : public QObject  // 定义 servoDevice 类，继承 QObject
{
    Q_OBJECT  // Qt 的宏，启用信号和槽机制

public:
    servoDevice();  // 构造函数
    void initServo();  // 初始化舵机
    void steerServo(int percent);  // 控制舵机转动到指定角度（百分比）
    void closeServo();  // 关闭舵机
    ~servoDevice();  // 析构函数

private:
    int fd = 0;  // 文件描述符，用于访问设备文件
};

#endif // SERVODEVICE_H  // 结束头文件包含保护
