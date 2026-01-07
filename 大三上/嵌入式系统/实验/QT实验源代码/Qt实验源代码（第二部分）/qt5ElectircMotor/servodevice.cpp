#include "servodevice.h"  // 包含舵机设备类的头文件

// 构造函数
servoDevice::servoDevice()
{
    // 构造函数体为空
}

// 初始化舵机：打开设备节点
void servoDevice::initServo()
{
    fd = open("/dev/servo", O_RDWR);  // 以读写方式打开设备文件
    if (fd < 0)  // 检查文件描述符是否正确打开
    {
        perror("open");  // 打开失败，输出错误信息
    }
}

// 控制舵机角度：通过 ioctl 调用
void servoDevice::steerServo(int percent)
{
    if (percent >= 0 && percent <= 180)  // 检查输入的角度是否在有效范围内
    {
        if (ioctl(fd, SET_ANGLE, percent) < 0)  // 发送控制命令
        {
            qDebug() << "ioctl SET_ANGLE failed";  // 如果命令发送失败，输出调试信息
        }
    }
}

// 关闭舵机设备：关闭设备节点
void servoDevice::closeServo()
{
    printf("Servofd:%d\n", fd);  // 打印设备文件描述符
    int ret = 0;
    if (fd > 0) {  // 检查文件描述符是否有效
        ret = close(fd);  // 尝试关闭文件描述符
        if (ret < 0) {  // 检查关闭操作是否成功
            perror("closeServo\n");  // 输出错误信息
        }
        fd = 0;  // 重置文件描述符
    }
}

// 析构函数
servoDevice::~servoDevice()
{
    close(fd);  // 在对象被销毁时关闭文件描述符
}
