#ifndef STEPPERDEVICE_H  // 防止头文件重复包含
#define STEPPERDEVICE_H

#include <QObject>  // 包含 QObject 类的定义
#include <stdio.h>  // 标准输入输出库
#include <fcntl.h>  // 文件控制定义
#include <sys/types.h>  // 包含基本系统数据类型
#include <sys/stat.h>  // 包含文件状态的定义
#include <sys/ioctl.h>  // 定义 ioctl() 系统调用
#include <unistd.h>  // 提供对 POSIX 操作系统 API 的访问
#include <QDebug>  // 包含 Qt 调试输出的功能
#include <QThread>

#define STEPPER_ON 0
#define STEPPER_OFF 1

// 步进电机设备类，继承自 QObject
class stepperDevice : public QObject
{
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    stepperDevice();  // 构造函数
    void initstepper();  // 初始化步进电机
    void run();  // 运行步进电机
    void setPart(int part);  // 设置步进电机的分区时间
    void changeRunningState(bool state);  // 更改步进电机的运行状态
    void closeStepper();  // 关闭步进电机
    ~stepperDevice();  // 析构函数

    bool isrun = true;  // 标识步进电机是否在运行

private:
    int stepperfd = 0;  // 步进电机的文件描述符
    int partTime = 0;  // 步进电机的部分时间控制
};

#endif // STEPPERDEVICE_H  // 结束头文件包含保护
