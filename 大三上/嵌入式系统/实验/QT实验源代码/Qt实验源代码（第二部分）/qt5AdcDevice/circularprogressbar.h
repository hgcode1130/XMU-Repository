#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

// 定义一个圆形进度条类
class Circularprogressbar : public QWidget
{
    Q_OBJECT
public:
    // 构造函数
    explicit Circularprogressbar(QWidget *parent = nullptr);

    // 设置进度条的当前值
    void setValue(int value);

    // 设置进度条颜色
    void setValueColor(const QColor& color);

    // 设置电压值
    void setVoltage(int voltage);

    // 设置电流值
    void setCurrent(int current);

protected:
    // 绘图事件处理函数
    void paintEvent(QPaintEvent *event);

private:
    // 绘制边缘部分
    void paintSide(QPainter *painter);

    // 绘制外圈
    void paintOutE(QPainter *painter);

    // 绘制线条
    void paintLine(QPainter *painter);

    // 绘制底部圆圈
    void paintBottomCircle(QPainter *painter);

    // 绘制内圈
    void paintInE(QPainter *painter);

    // 绘制内部圆圈
    void paintInnerCircle(QPainter *painter);

    // 绘制数值显示
    void paintValue(QPainter *painter);

private:
    int outRadis; // 外圆半径
    int inRadis; // 内圆半径
    int side; // 边长
    int value; // 显示的数值
    QColor valueColor; // 数值颜色
    int voltage; // 电压值
    int current; // 电流值
};

#endif // CIRCULARPROGRESSBAR_H
