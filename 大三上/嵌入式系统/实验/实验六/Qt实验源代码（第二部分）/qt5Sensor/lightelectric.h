#ifndef LIGHTELECTRIC_H  // 防止头文件重复包含
#define LIGHTELECTRIC_H

#include <QObject>  // 包含 QObject 类的定义
#include <QDebug>  // 包含 Qt 调试输出的功能
#include <QRunnable>  // 包含可在线程中运行任务的类定义
#include <stdio.h>  // 标准输入输出库
#include <fcntl.h>  // 文件控制定义
#include <unistd.h>  // 提供对 POSIX 操作系统 API 的访问
#include <stdlib.h>  // 标准库定义
#include <sys/ioctl.h>  // 定义 ioctl() 系统调用

// 电光设备类，继承自 QObject
class lightElectric : public QObject
{
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    explicit lightElectric(QObject *parent = nullptr);  // 构造函数
    void openlightElectric();  // 打开电光设备
    void readState();  // 读取电光设备的当前状态
    void changeLightState(bool state);  // 改变电光设备的状态
    void closeLightElectric();  // 关闭电光设备

signals:
    void sendState(int state);  // 发送电光设备的状态信号

private:
    int lightfd = 0;  // 电光设备的文件描述符
    int lightState = 0;  // 电光设备的当前状态
    bool isLightElectricRunning = true;  // 标识电光设备是否在运行
};

// 用于读取电光设备状态的任务类，实现 QRunnable 接口
class ReadLightStateTask : public QRunnable
{
private:
    lightElectric* lightDevice;  // 指向电光设备对象的指针

public:
    explicit ReadLightStateTask(lightElectric* device) : lightDevice(device) {
        setAutoDelete(true);  // 设置任务执行完毕后自动删除
    }

    void run() override {  // 任务执行函数
        if (lightDevice) {
            lightDevice->readState();  // 调用电光设备的 readState 方法
        }
    }
};

#endif // LIGHTELECTRIC_H  // 结束头文件包含保护
