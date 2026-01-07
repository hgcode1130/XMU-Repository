#ifndef TEMDEVICE_H  // 防止头文件重复包含
#define TEMDEVICE_H

#include <QObject>  // 包含 QObject 类的定义
#include <QDebug>  // 包含 Qt 调试输出的功能
#include <QRunnable>  // 包含可在线程中运行任务的类定义
#include <QThread>  // 包含线程管理的类定义
#include <stdio.h>  // 标准输入输出库
#include <stdlib.h>  // 标准库定义
#include <unistd.h>  // 提供对 POSIX 操作系统 API 的访问
#include <fcntl.h>  // 文件控制定义
#include <sys/ioctl.h>  // 定义 ioctl() 系统调用
#define I2C_RETRIES 0x0701
#define I2C_TIMEOUT 0x0702
#define I2C_RDWR 0x0707
/*********定义struct i2c_rdwr_ioctl_data和struct
 * i2c_msg，要和内核一致*******/


// 温度设备类，继承自 QObject
class temDevice : public QObject
{
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    explicit temDevice(QObject *parent = nullptr);  // 构造函数
    void openTemDevice();  // 打开温度设备
    void readData();  // 读取温度数据
    void changeThreadState(bool state);  // 改变读取数据线程的运行状态
    void closeTemFd();  // 关闭温度设备

signals:
    void sendData(float data);  // 发送温度数据的信号

private:
    int temfd = 0;  // 温度设备的文件描述符
    unsigned char data[2]= {0};  // 存储读取的数据
    float val = 0;  // 存储转换后的温度值
    bool isTemRunning = true;  // 标识温度读取线程是否在运行
    struct i2c_msg
    {
        unsigned short addr;
        unsigned short flags;
    #define I2C_M_TEN 0x0010
    #define I2C_M_RD 0x0001
        unsigned short len;
        unsigned char *buf;
    };
    struct i2c_rdwr_ioctl_data
    {
        struct i2c_msg *msgs;
        int nmsgs;
        /* nmsgs这个数量决定了有多少开始信号，对于“单开始时序”，取1*/
    };
};

// 用于读取温度数据的任务类，实现 QRunnable 接口
class ReadTemDataTask : public QRunnable
{
private:
    temDevice* tem;  // 指向温度设备对象的指针

public:
    explicit ReadTemDataTask(temDevice* device) : tem(device) {
        setAutoDelete(true);  // 设置任务执行完毕后自动删除
    }

    void run() override {  // 任务执行函数
        if (tem) {
            tem->readData();  // 调用温度设备的 readData 方法
        }
    }
};

#endif // TEMDEVICE_H  // 结束头文件包含保护
