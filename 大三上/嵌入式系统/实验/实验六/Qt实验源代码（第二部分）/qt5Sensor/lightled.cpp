#include "lightled.h"  // 包含 lightLed 类的定义

// 构造函数
lightLed::lightLed(QWidget *parent)
: QWidget(parent)
{
    posX = 0;  // LED 的初始横向位置设置为 0
    posY = 0;  // LED 的初始纵向位置设置为 0
}

// 设置 LED 的颜色并更新显示
void lightLed::setLedColor(const QString &newColor)
{
    ledColor = newColor;  // 更新 LED 的颜色
    update();  // 请求重绘 QWidget，触发 paintEvent
}

// 设置 LED 的大小并更新显示
void lightLed::setLedSize(int newSize)
{
    ledSize = newSize;  // 更新 LED 的大小
    update();  // 请求重绘
}

// 设置 LED 的纵向位置并更新显示
void lightLed::setLedYPosition(int y)
{
    posY = y;  // 更新 LED 的纵向位置
    update();  // 请求重绘
}

// 设置 LED 的横向位置并更新显示
void lightLed::setLedXPosition(int x)
{
    posX = x;  // 更新 LED 的横向位置
    update();  // 请求重绘
}

// 析构函数
lightLed::~lightLed()
{
    // 析构时无需额外操作
}

// 绘制事件处理函数，负责绘制 LED
void lightLed::paintEvent(QPaintEvent *)
{
    QPainter painter(this);  // 创建 QPainter 对象用于绘制
    painter.translate(posX, posY);  // 将绘制原点移动到 LED 的位置
    painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿

    painter.setPen(Qt::transparent);  // 设置画笔透明
    painter.fillRect(-width(), -height(), width() * 2, height() * 2, Qt::transparent);  // 绘制透明背景

    int radius = ledSize;  // LED 的半径

    // 绘制外边框
    QLinearGradient lg1(0, -radius, 0, radius);
    lg1.setColorAt(0, QColor(255, 255, 255));  // 渐变开始颜色
    lg1.setColorAt(1, QColor(166, 166, 166));  // 渐变结束颜色
    painter.setBrush(lg1);  // 设置画刷
    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);  // 绘制圆形外边框

    // 绘制内边框
    radius -= 13;
    QLinearGradient lg2(0, -radius, 0, radius);
    lg2.setColorAt(0, QColor(155, 155, 155));
    lg2.setColorAt(1, QColor(255, 255, 255));
    painter.setBrush(lg2);
    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);

    // 绘制 LED 内部的颜色
    radius -= 4;
    QRadialGradient rg(0, 0, radius);
    if (ledColor.compare("red") == 0) {
        rg.setColorAt(0, QColor(245, 0, 0));
        rg.setColorAt(0.6, QColor(210, 0, 0));
        rg.setColorAt(1, QColor(140, 0, 0));
    } else if (ledColor.compare("green") == 0) {
        rg.setColorAt(0, QColor(0, 245, 0));
        rg.setColorAt(0.6, QColor(0, 210, 0));
        rg.setColorAt(1, QColor(0, 140, 0));
    } else if (ledColor.compare("gray") == 0) {
        rg.setColorAt(0, QColor(245, 245, 245));
        rg.setColorAt(0.6, QColor(210, 210, 210));
        rg.setColorAt(1, QColor(140, 140, 140));
    }
    painter.setBrush(rg);  // 设置径向渐变画刷
    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);  // 绘制内部圆形

    // 绘制高光效果
    radius -= 3;
    QPainterPath path;
    path.addEllipse(-radius, -radius - 2, radius << 1, radius << 1);  // 高光的形状
    QPainterPath bigEllipse;
    radius *= 2;
    bigEllipse.addEllipse(-radius, -radius + 140, radius << 1, radius << 1);
    path -= bigEllipse;  // 形状运算，减去大圆形，留下高光部分
    QLinearGradient lg3(0, -radius / 2, 0, 0);
    lg3.setColorAt(0, QColor(255, 255, 255, 220));  // 高光开始颜色
    lg3.setColorAt(1, QColor(255, 255, 255, 30));  // 高光结束颜色
    painter.setBrush(lg3);  // 设置画刷
    painter.drawPath(path);  // 绘制高光
}
