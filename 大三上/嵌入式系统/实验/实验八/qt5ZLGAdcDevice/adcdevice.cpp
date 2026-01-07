#include "adcdevice.h"

// ADC设备的基类构造函数
AdcDevice::AdcDevice()
{
}

// 基类的ReadAdc函数，目前为空实现，派生类需要重写此函数
void AdcDevice::ReadAdc()
{
    int ret = Run();  // 执行ADC读取操作

    if(ret < 0)  // 判断读取是否成功
    {
        qDebug()<<"read failed";  // 如果读取失败，输出错误信息
    }
    else
    {
        Vol = ret;
    }
}

float AdcDevice::getCurrent()
{
}

int AdcDevice::getVoltage()
{
    return Vol;
}


