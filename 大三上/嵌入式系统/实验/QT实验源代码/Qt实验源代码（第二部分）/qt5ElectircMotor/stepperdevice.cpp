#include "stepperdevice.h"  // 包含 stepperDevice 类的定义

// 构造函数
stepperDevice::stepperDevice()
{
    // 构造函数中没有执行特定操作
}

// 初始化步进电机
void stepperDevice::initstepper()
{
    stepperfd = open("/dev/stepper", O_RDWR);  // 尝试以读写方式打开步进电机设备
    if (stepperfd < 0) {
        perror("open");  // 打开失败时，输出错误信息
    }
}

// 运行步进电机
void stepperDevice::run()
{
    ioctl(stepperfd, STEPPER_OFF, 3);
    ioctl(stepperfd, STEPPER_OFF, 2);
    ioctl(stepperfd, STEPPER_OFF, 1);
    ioctl(stepperfd, STEPPER_OFF, 0);
    isrun = true;  // 设置运行标志为真，开始循环
    while (isrun) {  // 循环，直到外部标志 isrun 被设置为 false
        qDebug()<<"run";
        ioctl(stepperfd, STEPPER_ON, 0);
        ioctl(stepperfd, STEPPER_OFF, 1);
        ioctl(stepperfd, STEPPER_OFF, 2);
        ioctl(stepperfd, STEPPER_OFF, 3);
        QThread::usleep(partTime);

        qDebug()<<"run1";
        ioctl(stepperfd, STEPPER_ON, 0);
        ioctl(stepperfd, STEPPER_ON, 1);
        ioctl(stepperfd, STEPPER_OFF, 2);
        ioctl(stepperfd, STEPPER_OFF, 3);
        QThread::usleep(partTime);

        qDebug()<<"run2";
        ioctl(stepperfd, STEPPER_OFF, 0);
        ioctl(stepperfd, STEPPER_ON, 1);
        ioctl(stepperfd, STEPPER_OFF, 2);
        ioctl(stepperfd, STEPPER_OFF, 3);
        QThread::usleep(partTime);

        qDebug()<<"run3";
        ioctl(stepperfd, STEPPER_OFF, 0);
        ioctl(stepperfd, STEPPER_ON, 1);
        ioctl(stepperfd, STEPPER_ON, 2);
        ioctl(stepperfd, STEPPER_OFF, 3);
        QThread::usleep(partTime);

        qDebug()<<"run4";
        ioctl(stepperfd, STEPPER_OFF, 0);
        ioctl(stepperfd, STEPPER_OFF, 1);
        ioctl(stepperfd, STEPPER_ON, 2);
        ioctl(stepperfd, STEPPER_OFF, 3);
        QThread::usleep(partTime);

        qDebug()<<"run5";
        ioctl(stepperfd, STEPPER_OFF, 0);
        ioctl(stepperfd, STEPPER_OFF, 1);
        ioctl(stepperfd, STEPPER_ON, 2);
        ioctl(stepperfd, STEPPER_ON, 3);
        QThread::usleep(partTime);

        qDebug()<<"run6";
        ioctl(stepperfd, STEPPER_OFF, 0);
        ioctl(stepperfd, STEPPER_OFF, 1);
        ioctl(stepperfd, STEPPER_OFF, 2);
        ioctl(stepperfd, STEPPER_ON, 3);
        QThread::usleep(partTime);

        qDebug()<<"run7";
        ioctl(stepperfd, STEPPER_ON, 0);
        ioctl(stepperfd, STEPPER_OFF, 1);
        ioctl(stepperfd, STEPPER_OFF, 2);
        ioctl(stepperfd, STEPPER_ON, 3);
        QThread::usleep(partTime);
        qDebug()<<"partTime"<<partTime;
    }
}

// 设置步进电机的频率
void stepperDevice::setPart(int part)
{
    isrun = true;  // 确保运行标志为真
    switch (part) {  // 根据传入的参数设置部分时间
    case 0:  // 如果是 0，则关闭所有步进
        ioctl(stepperfd, STEPPER_OFF, 3);
        ioctl(stepperfd, STEPPER_OFF, 2);
        ioctl(stepperfd, STEPPER_OFF, 1);
        ioctl(stepperfd, STEPPER_OFF, 0);
        isrun = false;  // 设置运行标志为假，停止运行
        break;
    case 1:
        partTime = 5000;  // 设置步进时间
        break;
    case 2:
        partTime = 3000;
        break;
    case 3:
        partTime = 2000;
        break;
    case 4:
        partTime = 900;
        break;
    default:
        break;
    }
}

// 更改步进电机的运行状态
void stepperDevice::changeRunningState(bool state)
{
    isrun = state;  // 根据传入的状态设置运行标志
}

// 关闭步进电机
void stepperDevice::closeStepper()
{
    printf("stepperfd:%d\n", stepperfd);  // 输出步进电机文件描述符
    int ret = 0;
    if (stepperfd > 0) {
        ret = close(stepperfd);  // 尝试关闭文件描述符
        if (ret < 0) {
            perror("closeStepper\n");  // 关闭失败时输出错误信息
        }
        stepperfd = 0;  // 重置文件描述符
    }
}

// 析构函数
stepperDevice::~stepperDevice()
{
    close(stepperfd);  // 确保在对象销毁时关闭文件描述符
}
