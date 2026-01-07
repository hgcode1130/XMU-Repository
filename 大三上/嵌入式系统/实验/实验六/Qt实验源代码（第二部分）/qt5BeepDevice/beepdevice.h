#ifndef BEEPDEVICE_H
#define BEEPDEVICE_H

#include <string>
#include <QObject>
#include <QDebug>
#include <QWidget>

extern "C" {
#include "hal_fs3399_beep.h"  // 引入蜂鸣器控制的头文件
}

using namespace std;

// beepDevice类，用于控制蜂鸣器
class beepDevice : public QObject {
    Q_OBJECT
public:
    beepDevice();

    // 打开蜂鸣器
    int beepOn();

    //  关闭蜂鸣器
    int beepOff();

    ~beepDevice();
};

#endif // BEEPDEVICE_H
