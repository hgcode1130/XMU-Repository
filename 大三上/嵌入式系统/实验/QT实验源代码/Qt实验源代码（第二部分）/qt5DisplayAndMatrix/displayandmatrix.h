#ifndef DISPLAYANDMATRIX_H  // 防止重复包含
#define DISPLAYANDMATRIX_H

extern "C"  // 使用 C 链接规范，以便与 C 代码兼容
{
#include "hal_displayandmatrix.h"  // 包含硬件抽象层的头文件
}

#include <QDebug>
#include <QObject>

// 基础类 DisplayandMatrix，继承自 QObject
class DisplayandMatrix : public QObject
{
    Q_OBJECT  // Qt 对象宏

public:
    DisplayandMatrix(); // 默认构造函数

    char getValue();
    void trunNewBuf(char value);
    void close();
};


#endif // DISPLAYANDMATRIX_H
