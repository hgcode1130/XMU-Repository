#ifndef RFIDDEVICE_H  // 防止头文件重复包含
#define RFIDDEVICE_H

extern "C" {
    #include "hal_rfid.h"  // 引入 C 风格的 RFID 硬件抽象层头文件
}

#include <QDebug>  // 引入 Qt 的调试输出模块

// 定义 RfidDevice 类
class RfidDevice :public QObject
{
    Q_OBJECT
public:
    RfidDevice();  // 构造函数
    ~RfidDevice();
    void func_init(int rfid);  // 初始化 RFID 设备
    void closeRfid();  // 关闭 RFID 设备

    // 以下函数用于读取不同频率的 RFID 标签
    QString readHf();  // 读取高频（HF）标签
    QString readLf();  // 读取低频（LF）标签
    QString readNfc();  // 读取近场通信（NFC）标签
    QString read2_4G();  // 读取2.4G标签
    QString read915M();  // 读取915M频段的标签

signals:
    void sendHf(QString hf);
    void sendLf(QString lf);
    void sendNfc(QString nfc);
    void send2_4G(QString f2_4G);
    void send915M(QString f915M);
};

#endif // RFIDDEVICE_H
