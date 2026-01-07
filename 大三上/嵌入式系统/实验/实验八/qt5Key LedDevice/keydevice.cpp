#include "keydevice.h"
using namespace std;

// KeyDevice类的构造函数，用于初始化键盘设备。
KeyDevice::KeyDevice()
{
    key_init(); // 初始化键盘设备
}

// 获取按键状态的函数，会持续检测按键是否被按下。
void KeyDevice::getKeys()
{
    while (1) // 无限循环，持续检测按键
    {
        int ret = get_keys_clicked(); // 获取被按下的按键
        if (ret < 0) // 如果返回值小于0，表示获取按键失败
            qDebug() << "get Keys faile"; // 输出错误信息
        emit KeysState(ret); // 发射信号，传递按键状态
    }
}

// KeyDevice类的析构函数，用于关闭键盘设备。
KeyDevice::~KeyDevice()
{
    key_close(); // 关闭键盘设备
}

// ledDvice类的构造函数，用于初始化LED设备。
ledDvice::ledDvice()
{
    led_init(); // 初始化LED设备
}

// ledDvice类的析构函数，用于关闭LED设备。
ledDvice::~ledDvice()
{
    led_close(); // 关闭LED设备
}

// 打开指定编号的LED的函数。
int ledDvice::ledOn(int nr)
{
    int ret = 0;
    ret = led_on(nr); // 尝试打开编号为nr的LED
    if (ret < 0) // 如果返回值小于0，表示打开LED失败
        perror("open led failed\n"); // 输出错误信息
    return ret; // 返回操作结果
}

// 关闭指定编号的LED的函数。
int ledDvice::ledOff(int nr)
{
    int ret = 0;
    ret = led_off(nr); // 尝试关闭编号为nr的LED
    if (ret < 0) // 如果返回值小于0，表示关闭LED失败
        perror("close led failed\n"); // 输出错误信息
    return ret; // 返回操作结果
}

// 关闭LED设备的函数。
int ledDvice::ledClose()
{
    return led_close(); // 关闭LED设备并返回操作结果
}