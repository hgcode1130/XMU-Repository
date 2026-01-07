#ifndef SEMICIRCULAR_H  // 防止头文件重复包含
#define SEMICIRCULAR_H

#include <QWidget>  // 包含 QWidget 类的定义
#include <QPainter>  // 包含画笔类，用于绘图
#include <QPainterPath>  // 包含路径类，用于复杂形状的绘制
#include <QtMath>  // 提供数学函数
#include <QTimer>  // 包含定时器类
#include <QKeyEvent>  // 包含键盘事件类
#include <QDebug>  // 包含调试输出功能
#include <algorithm>  // 包含算法库

// 半圆仪表盘类，继承自 QWidget
class SemiCircular : public QWidget
{
    Q_OBJECT  // 启用 Qt 的信号和槽机制

public:
    explicit SemiCircular(QWidget *parent = nullptr);  // 构造函数
    // 定制大小
    void changeSize(int size);
    // 绘制最外圈线
    void drawOutermostLine(QPainter &painter, int radius);
    // 绘制渐变区域
    void drawGradientArea(QPainter &painter, int radius);
    // 放置刻度的圈
    void drawOutMiddleCircle(QPainter &painter, int radius);
    // 绘制中间最小的圆
    void drawMiddleLittleCircle(QPainter &painter, int radius);
    // 中间第二大圆
    void drawMiddleCircle(QPainter &painter, int radius);
    // 中间最大圆
    void drawMiddleBiggestCircle(QPainter &painter, int radius);
    // 画圆剪切环形区域
    void drawCircle(QPainter &painter, int radius);
    // 画刻度
    void drawScale(QPainter &painter, int radius);
    // 画数字刻度
    void drawNumScale(QPainter &painter, int radius);
    // 显示单位
    void drawUnit(QPainter &painter, int radius);
    // 实时数据
    void drawRealTimeData(QPainter &painter, int radius);
    // 指针
    void drawPointer(QPainter &painter, int radius);
    // 重写绘制函数
    void paintEvent(QPaintEvent *) override;
    // 最大值函数
    int max(int a, double b) {
        return (a > b) ? a : b;
    }
    ~SemiCircular();  // 析构函数

public slots:
    void changeValue(int newvalue);  // 更改值的槽函数

private:
    int direction = 0;  // 指针方向
    int degRotate = 0;  // 旋转角度
    int value = 0;  // 当前值
    int mySize = 0;  // 当前尺寸
    int baseSize = 0;  // 基准尺寸
};

#endif // SEMICIRCULAR_H  // 结束头文件包含保护
