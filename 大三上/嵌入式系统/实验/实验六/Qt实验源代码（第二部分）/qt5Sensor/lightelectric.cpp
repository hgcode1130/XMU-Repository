#include "lightelectric.h"  // 包含 lightElectric 类的定义

// 构造函数
lightElectric::lightElectric(QObject *parent) : QObject(parent)
{
    lightfd = open("/dev/rk3399_itr", O_RDWR);  // 尝试以读写方式打开电光设备
    if (lightfd < 0) {  // 检查设备是否成功打开
        perror("open");  // 打开失败时，输出错误信息
    }
}

// 打开电光设备
void lightElectric::openlightElectric()
{
    lightfd = open("/dev/rk3399_itr", O_RDWR);  // 再次尝试以读写方式打开电光设备
    if (lightfd < 0) {  // 检查设备是否成功打开
        perror("open");  // 打开失败时，输出错误信息
    }
}

// 读取电光设备的状态
void lightElectric::readState()
{
    while(isLightElectricRunning){  // 在设备运行标志为真的情况下持续运行
        read(lightfd, &lightState, sizeof(int));  // 从设备文件读取状态
        emit sendState(lightState);  // 发送读取到的状态
        usleep(100000);  // 暂停100毫秒，减少CPU占用
    }
}

// 更改电光设备的运行状态
void lightElectric::changeLightState(bool state)
{
    isLightElectricRunning = state;  // 设置电光设备的运行状态
}

// 关闭电光设备
void lightElectric::closeLightElectric()
{
    close(lightfd);  // 关闭与电光设备关联的文件描述符
}
