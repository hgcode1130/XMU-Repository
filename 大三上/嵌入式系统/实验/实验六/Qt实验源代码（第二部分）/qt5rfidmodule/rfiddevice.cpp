#include "rfiddevice.h"  // 包含 RfidDevice 类的声明

// 构造函数实现，不执行任何操作
RfidDevice::RfidDevice()
{
}

RfidDevice::~RfidDevice()
{
    free(rfid_card);
}

// 初始化 RFID 设备
void RfidDevice::func_init(int rfid)
{
    int ret = init_rfid(rfid);  // 调用 C 层函数初始化 RFID 设备
    if (ret < 0) {
        qDebug() << "init failed";  // 输出初始化失败信息
    }
}

// 关闭 RFID 设备
void RfidDevice::closeRfid()
{
    qDebug() << "close_rfid";
    close_rfid();  // 调用 C 层函数关闭 RFID 设备
}

// 读取高频（HF）标签
QString RfidDevice::readHf()
{
    char* buf = read_hf();  // 调用 C 层函数读取 HF 标签数据
    QString str(buf);  // 将 C 字符串转换为 QString
    qDebug()<<"free Hf buf";
    emit sendHf(str);
    return str;  // 返回读取到的 HF 标签数据
}

// 读取低频（LF）标签
QString RfidDevice::readLf()
{
    char* buf = read_lf();  // 调用 C 层函数读取 LF 标签数据
    QString str(buf);  // 将 C 字符串转换为 QString
    emit sendLf(str);
    return str;  // 返回读取到的 LF 标签数据
}

// 读取近场通信（NFC）标签
QString RfidDevice::readNfc()
{
    char* buf = read_nfc();  // 调用 C 层函数读取 NFC 标签数据
    QString str(buf);  // 将 C 字符串转换为 QString
    emit sendNfc(str);
    return str;  // 返回读取到的 NFC 标签数据
}

// 读取2.4G标签
QString RfidDevice::read2_4G()
{
    char* buf = read_2_4G();  // 调用 C 层函数读取 2_4G 标签数据
    QString str(buf);  // 将 C 字符串转换为 QString
    emit sendNfc(str);
    return str;  // 返回读取到的 NFC 标签数据
}

// 读取915M频段的标签
QString RfidDevice::read915M()
{
    char* buf = read_915m();  // 调用 C 层函数读取 2_4G 标签数据
    QString str(buf);  // 将 C 字符串转换为 QString
    emit sendNfc(str);
    return str;  // 返回读取到的 NFC 标签数据
}
