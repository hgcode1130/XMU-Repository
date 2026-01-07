#include "dcdevice.h"  // 包含 dcDevice 类的定义

// 构造函数
dcDevice::dcDevice()
{

}

// 初始化直流电机
void dcDevice::initDc()
{
    dcfd = 0;  // 初始化文件描述符
    dcfd = open("/dev/dc_motor", O_RDWR);  // 尝试以读写方式打开直流电机设备
    if (dcfd < 0) {  // 检查设备是否成功打开
        perror("open");  // 打开失败时，输出错误信息
    }
}

// 控制直流电机
void dcDevice::controlDc(int operation)
{
    switch (operation) {  // 根据传入的操作编号执行不同的控制命令
    case 0:
        ioctl(dcfd, DC_MOTOR_ON);  // 打开电机
        ioctl(dcfd, DC_MOTOR_DIR, &operation);  // 设置电机方向
        break;
    case 1:
        ioctl(dcfd, DC_MOTOR_ON);  // 打开电机
        ioctl(dcfd, DC_MOTOR_DIR, &operation);  // 设置电机方向
        break;
    case 2:
        ioctl(dcfd, DC_MOTOR_OFF);  // 关闭电机
        break;
    }
}

// 关闭直流电机
void dcDevice::closeDc()
{
    printf("dcfd:%d\n", dcfd);  // 输出文件描述符
    int ret = 0;
    if (dcfd > 0) {
        ret = close(dcfd);  // 尝试关闭文件描述符
        if (ret < 0) {
            perror("closedc\n");  // 关闭失败时输出错误信息
        }
        dcfd = 0;  // 重置文件描述符
    }
}

// 析构函数
dcDevice::~dcDevice()
{
    close(dcfd);  // 确保在对象销毁时关闭文件描述符
}
