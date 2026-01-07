#ifndef KEYDEVICE_H
#define KEYDEVICE_H

// 导入C语言编写的按键处理库
extern "C"
{
#include "hal_fs3399_key.h"
}

#include <QWidget>
#include <QDebug>

// KeyDevice用于定义按键设备接口
class KeyDevice : public QObject
{
    Q_OBJECT
public:
    KeyDevice();
    void getKeys();
    ~KeyDevice();

signals:
    // 定义一个信号，用于通知按键状态的变化
    void KeysState(int keyStates);
};

#endif // KEYDEVICE_H
