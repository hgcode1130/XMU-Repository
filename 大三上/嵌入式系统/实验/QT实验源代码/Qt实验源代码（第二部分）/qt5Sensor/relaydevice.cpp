#include "relaydevice.h"  // 包含 relayDevice 类的定义

// 构造函数
relayDevice::relayDevice(QObject *parent) : QObject(parent)
{
    relayfd = open("/dev/relay", O_RDWR);  // 尝试以读写方式打开继电器设备
    if (relayfd < 0) {  // 检查设备是否成功打开
        perror("open");  // 打开失败时，输出错误信息
    }
    ioctl(relayfd, RELAY_OFF);
}

// 打开继电器设备
void relayDevice::openRelayDevice()
{
    relayfd = open("/dev/relay", O_RDWR);  // 再次尝试以读写方式打开继电器设备
    if (relayfd < 0) {  // 检查设备是否成功打开
        perror("open");  // 打开失败时，输出错误信息
    }
    ioctl(relayfd, RELAY_OFF);
}

// 改变继电器的状态
int relayDevice::changeRelayState(int state)
{
    int newstate = 0;  // 用于存储继电器的新状态
    switch(state){
    case 1:
        ioctl(relayfd, RELAY_ON);  // 打开继电器
        break;
    case 0:
        ioctl(relayfd, RELAY_OFF);  // 关闭继电器
        break;
    default:
        // 如果传入未定义的状态，不执行任何操作
        break;
    }
/*    ioctl(relayfd, RELAY_STATE, &newstate);  // 读取并返回继电器的当前状态
    return newstate; */ // 返回继电器的状态
}

// 关闭继电器的文件描述符
void relayDevice::closeRelayFd()
{
    close(relayfd);  // 关闭与继电器设备关联的文件描述符
}
