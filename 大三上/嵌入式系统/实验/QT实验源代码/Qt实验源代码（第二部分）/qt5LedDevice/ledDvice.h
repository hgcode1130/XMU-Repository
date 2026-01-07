#ifndef LEDDVICE_H
#define LEDDVICE_H

#include <QObject>
#include <QWidget>
// 包含外部C语言头文件
extern "C"
{
#include "hal_fs3399_led.h"
}

// LED设备基类，提供LED操作的纯虚函数
class ledDvice : public QWidget {
    Q_OBJECT
public:
    ledDvice();
    ~ledDvice();
    
    // 用于打开特定的LED
    int ledOn(int nr);

    // 用于关闭特定的LED
    int ledOff(int nr);
    
    int ledClose();

};

#endif // LEDDVICE_H
