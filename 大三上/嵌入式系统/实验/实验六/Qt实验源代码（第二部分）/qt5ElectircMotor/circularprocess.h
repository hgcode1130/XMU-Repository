#ifndef CIRCULARPROCESS_H
#define CIRCULARPROCESS_H
#include <QWidget>
#include <QPainter>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <QTimer>
#include <QMouseEvent>
#include <QPainterPath>
class CircularProcess : public QWidget{
    Q_OBJECT

public:
    CircularProcess(QWidget *parent = nullptr);

    //绘制圆
    void drawDial(QPainter *painter);

    //绘制数据
    void drawText(QPainter *painter, QString unit);

    //设置不同档位的颜色
    void setDialusedColor(int value);

    //重写绘画事件以及鼠标事件
    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    //根据鼠标事件更新数值
    void updateValueFromMouseEvent(QMouseEvent *event);

    //根据数值更改圆弧
    void setValueFromPercent(double percent);

    ~CircularProcess();

    int outPutPrecent = 0;

private:
    QTimer *timer;

    double minValue;
    double maxValue;
    double value;
    double angle;
    int precision;

    double currentPercent;
    double valuePercent;

    QColor usedColor;
    QColor freeColor;

    QColor rangeTextColor;
    QColor valueTextColor;

    double temperaturePercent;
    double humidityPercent;

    QString unit;

    int sendpercent = 0;

public:
    double getMinValue()const
    {
        return minValue;
    }
    double getMaxValue()const
    {
        return maxValue;
    }
    double getValue()const
    {
        return value;
    }
    double getAngle()const
    {
        return angle;
    }
    int getPrecision()const
    {
        return precision;
    }

public slots:

    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    void setValue(double value, QString unit1);
    void setValue(int value, QString unit1);

    void setAngle(double angle);

    void setPrecision(int precision);

    void setUsedColor(QColor usedColor);

    void setFreeColor(QColor freeColor);

    void setRangeTextColor(QColor rangeTextColor);
    void setValueTextColor(QColor valueTextColor);

private slots:
    void updateValue();

signals:
    void angleChanged(int percent);
    void valueChanged(double value);

};
#endif //CIRCULARPROCESS_H
