#ifndef MIXADCDEVICE_H
#define MIXADCDEVICE_H
#include <QObject>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <QMap>
#include <QString>
#include <QDebug>
#include <QRunnable>
#include <QThread>
#include <iostream>
#include <fstream>
#include <string>

// 定义了一些常量，用于选择 ADC 设备的不同通道
#define SET_CHANNEL _IO('A', 0)

class mixAdcDevice : public QObject
{
    Q_OBJECT
public:
    // 构造函数，创建 mixAdcDevice 实例时调用
    explicit mixAdcDevice(QObject *parent = nullptr);

    // 打开 ADC 设备文件描述符
    void openAdcDevice(QString function);

    // 读取 ADC 设备的数据
    void readData(QString function);

    // 改变线程状态，用于控制读取数据的线程是否运行
    void changeThreadState(bool state);

    // 关闭 ADC 设备文件描述符
    void closeAdcFd();
    
    static int filter(const struct dirent *entry);

signals:
    // 信号，当需要发送数据时发出
    void sendData(int data);

private:
    // ADC 设备的文件描述符
    int adcfd = 0;

    // 通道映射，用于映射功能到通道号
    QMap<QString, int> channelMap;

    // 标志位，表示 ADC 是否正在运行
    bool isAdcRunning = true;
};

class ReadAdcDataTask : public QRunnable
{
private:
    // 指向 mixAdcDevice 实例的指针
    mixAdcDevice* adcDevice;
public:
    // 构造函数，创建 ReadAdcDataTask 实例时调用
    explicit ReadAdcDataTask(mixAdcDevice* device,QString Func) : adcDevice(device) ,Function(Func){
        setAutoDelete(true); // 确保任务完成后自动删除
    }

    // 运行函数，在线程中执行读取 ADC 数据的操作
    void run() override {
        if (adcDevice) { 
            adcDevice->changeThreadState(true);
            adcDevice->readData(Function);
        }
    }


private:
    QString Function;
};

#endif // MIXADCDEVICE_H
