#ifndef RELAYDEVICE_H  // 防止头文件重复包含
#define RELAYDEVICE_H

#include <QObject>  // 包含 QObject 类的定义
#include <stdio.h>  // 标准输入输出库
#include <fcntl.h>  // 文件控制定义
#include <unistd.h>  // 提供对 POSIX 操作系统 API 的访问
#include <stdlib.h>  // 标准库定义
#include <sys/ioctl.h>  // 定义 ioctl() 系统调用

//#define IOCTL_MAGIC 'R'  // 定义 IOCTL 的魔数
//#define RELAY_ON _IO(IOCTL_MAGIC, 0)  // 定义打开继电器的命令
//#define RELAY_OFF _IO(IOCTL_MAGIC, 1)  // 定义关闭继电器的命令
//#define RELAY_STATE _IOR(IOCTL_MAGIC, 2, int)  // 定义读取继电器状态的命令


#define RELAY_ON 0
#define RELAY_OFF 1

// 继电器设备类
class relayDevice : public QObject
{
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    explicit relayDevice(QObject *parent = nullptr);  // 构造函数
    void openRelayDevice();  // 打开继电器设备
    int changeRelayState(int state);  // 改变继电器的状态
    void closeRelayFd();  // 关闭继电器设备文件描述符

private:
    int relayfd = 0;  // 继电器设备的文件描述符
};

#endif // RELAYDEVICE_H  // 结束头文件包含保护
