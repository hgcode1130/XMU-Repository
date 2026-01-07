#ifndef CIRCULARPROCESS_H
#define CIRCULARPROCESS_H
#include <QWidget>
#include "temdevice.h"
#include <QPainter>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <QTimer>

class CircularProcess : public QWidget{
    Q_OBJECT

public:
    CircularProcess(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void drawDial(QPainter *painter);
    void drawText(QPainter *painter, QString unit);
    void setDialusedColor(int value);
    void setRandomValue();
    ~CircularProcess();

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
    void valueChanged(double value);

};
#endif //CIRCULARPROCESS_H
