#ifndef LIGHTLED_H  // 防止头文件重复包含
#define LIGHTLED_H

#include <QWidget>  // 包含 QWidget 类的定义
#include <QPainter>  // 包含画笔类，用于绘图
#include <QPainterPath>  // 包含路径类，用于复杂形状的绘制
#include <QTimer>  // 包含定时器类，用于定时更新
#include <QDebug>  // 包含调试输出的功能

// 自定义 LED 灯显示类，继承自 QWidget
class lightLed : public QWidget {
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    explicit lightLed(QWidget *parent = nullptr);  // 构造函数
    ~lightLed();  // 析构函数
    void setLedColor(const QString &newColor);  // 设置 LED 的颜色
    void setLedSize(int newSize);  // 设置 LED 的大小
    void setLedXPosition(int x);  // 设置 LED 的横向位置
    void setLedYPosition(int y);  // 设置 LED 的纵向位置

protected:
    void paintEvent(QPaintEvent *) override;  // 重写的绘图事件，用于绘制 LED

private:
    QString ledColor;  // LED 的颜色
    int ledSize;  // LED 的大小
    int posX, posY;  // LED 的位置坐标
    QTimer *updatatimer;  // 更新定时器，用于周期性重绘 LED
};

#endif // LIGHTLED_H  // 结束头文件包含保护
