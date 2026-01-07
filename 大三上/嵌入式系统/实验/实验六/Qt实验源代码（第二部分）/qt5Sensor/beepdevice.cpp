#include "beepdevice.h"  // 包含蜂鸣器设备类的头文件

// 构造函数
beepDevice::beepDevice(QObject *parent) : QObject(parent)
{
    beepfd = open("/dev/buzzer", O_RDWR);  // 以读写方式尝试打开蜂鸣器设备
    if (beepfd < 0) {  // 检查设备是否成功打开
        perror("open");  // 打开失败，输出错误信息
    }
    ioctl(beepfd , BEEP_OFF);
}

// 打开蜂鸣器设备
void beepDevice::openBeepDevice()
{
    beepfd = open("/dev/buzzer", O_RDWR);  // 再次以读写方式打开设备
    if (beepfd < 0) {  // 检查设备是否成功打开
        perror("open");  // 打开失败，输出错误信息
    }
    ioctl(beepfd , BEEP_OFF);
}

// 更改蜂鸣器状态
void beepDevice::changeBeepState(int state)
{
    //int max = 1;  // 设置蜂鸣器的最大频率为 1
    //ioctl(beepfd, SET_FREQUENCY, &max);  // 通过 IOCTL 调用设置蜂鸣器的频率

    switch(state){
    case 1:  // 如果状态为 1，打开蜂鸣器
        ioctl(beepfd, BEEP_ON);
        qDebug() << "BEEP_ON";  // 输出调试信息，表明蜂鸣器已开启
        break;
    case 0:  // 如果状态为 0，关闭蜂鸣器
        ioctl(beepfd, BEEP_OFF);
        qDebug() << "BEEP_OFF";  // 输出调试信息，表明蜂鸣器已关闭
        break;
    default:
        // 其他值不做处理
        break;
    }
}

// 关闭蜂鸣器的文件描述符
void beepDevice::closeBeepFd()
{
    close(beepfd);  // 关闭与蜂鸣器设备关联的文件描述符
}
