#ifndef ADCDEVICE_H
#define ADCDEVICE_H

#include <QWidget>
#include <QDebug>
// 包含C语言编写的硬件抽象层ADC库
extern "C" {
#include "hal_fs3399_adc.h"
}
#include <QThread>

// AdcDevice 是一个抽象基类，用于定义ADC设备的接口
class AdcDevice : public QObject {
Q_OBJECT
public:
    AdcDevice();
    // 用于读取ADC数据
    void ReadAdc();
    // 获取当前电流值
    float getCurrent();
    // 获取当前电压值
    int getVoltage();

private:
    int Vol = 0;

signals:
    void adcDataUpdated();  // 数据更新信号
};


// 用于持续读取ADC数据的线程类
class UpdateThread : public QThread {
Q_OBJECT
private:
    AdcDevice* adcDevice;  // 持有一个AdcDevice对象

public:
    UpdateThread(AdcDevice* adcDevice) : adcDevice(adcDevice) {}

protected:
    void run() {
        qDebug()<<"run";
        while (true) {
            adcDevice->ReadAdc();  // 读取ADC数据
            emit adcDevice->adcDataUpdated();  // 发射数据更新信号
            msleep(1000);  // 每秒更新一次
        }
    }
};

#endif // ADCDEVICE_H
