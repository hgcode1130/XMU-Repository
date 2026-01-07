#include "circularprocess.h"
#include <QPushButton>

CircularProcess::CircularProcess(QWidget *parent)
    : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start(1000);
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    setPalette(palette);
    minValue = -45;
    maxValue = 45;
    value = 0;
    precision = 0;
    angle = 40;
    unit = "";
    currentPercent = 0;
    valuePercent = 0;
    freeColor = QColor(215, 215, 215);
}

void CircularProcess::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width / 2, height / 2);
    int side = qMin(width, height);
    painter.scale(side / 200.0, side / 200.0);
    painter.fillRect(rect(), palette().color(QPalette::Background));
    drawDial(&painter);
    drawText(&painter,unit);
}

void CircularProcess::drawDial(QPainter *painter)
{
    int radius = 95;
    double lineWidth = 2.5;
    painter->save();
    painter->rotate(angle);
    setDialusedColor(currentPercent);
    double rotate = (double)(360 - (angle * 2)) / 100;
    painter->setPen(QPen(usedColor, lineWidth));
    for (double i = 0; i < currentPercent; i++) {
        painter->drawLine(0, radius, 0, radius / 1.2);
        painter->rotate(rotate);
    }
    painter->setPen(QPen(freeColor, lineWidth));
    for (double i = currentPercent; i < 100; i++) {
        painter->drawLine(0, radius, 0, radius / 1.2);
        painter->rotate(rotate);
    }
    painter->restore();
}

void CircularProcess::setDialusedColor(int valcurrentPercentue)
{
   if(valcurrentPercentue > 0 && currentPercent <= 50)
   {
       usedColor = QColor(30, 144, 255);
   }
   else if(currentPercent > 50 && currentPercent <= 65)
   {
       usedColor = QColor(165, 220, 62);
   }
   else if(currentPercent > 65 && currentPercent <= 85)
   {
       usedColor = QColor(255, 185, 15);
   }
   else
   {
       usedColor = QColor(255, 0, 0);
   }
}

void CircularProcess::drawText(QPainter *painter,QString unit)
{
    int radius = 100;
    painter->save();
    double currentValue = currentPercent * ((maxValue - minValue) / 100) + minValue;
    if (currentValue > value) {
        currentValue = value;
    }
    QString strValue = QString("%1%2").arg(QString::number(currentValue, 'f', precision)).arg(unit);
    QString strMinValue = QString("%1%2").arg(minValue).arg(unit);
    QString strMaxValue = QString("%1%2").arg(maxValue).arg(unit);
    painter->setFont(QFont("Noto Sans CJK SC Regular", 13));
    painter->setPen(QPen(valueTextColor));
    QFontMetricsF fm = QFontMetricsF(painter->font());
    QSizeF size = fm.size(Qt::TextSingleLine, strValue);
    painter->drawText(-size.width() / 2, size.height() / 3, strValue);
    painter->setFont(QFont("Noto Sans CJK SC Regular", 8));
    painter->setPen(QPen(rangeTextColor));
    fm = QFontMetricsF(painter->font());
    size = fm.size(Qt::TextSingleLine, strMinValue);
    painter->drawText(-radius / 2 - size.width() / 2 + 8, 80, strMinValue);
    size = fm.size(Qt::TextSingleLine, strMaxValue);
    painter->drawText(radius / 2 - size.width() / 2 - 8, 80, strMaxValue);
    painter->restore();
}

void CircularProcess::updateValue()
{
    currentPercent = valuePercent;
    setValue(this->value,unit);
    update();
}

void CircularProcess::setRange(double minValue, double maxValue)
{
    if (minValue >= maxValue) {
        return;
    }
    currentPercent = 0;
    valuePercent = 100 * (this->value - this->minValue) / (this->maxValue - this->minValue);
    this->minValue = minValue;
    this->maxValue = maxValue;
    if (value < minValue || value > maxValue) {
        setValue(value,unit);
    }
}

void CircularProcess::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void CircularProcess::setValue(double value, QString unit1)
{
    if (value < minValue) {
        this->value = minValue;
    } else if (value > maxValue) {
        this->value = maxValue;
    } else {
        this->value = value;
    }
    unit = unit1;
    emit valueChanged(this->value);
    currentPercent = (valuePercent > 0) ? valuePercent : ((value - minValue) / (maxValue - minValue)) * 100;
    valuePercent = 100 * (this->value - this->minValue) / (this->maxValue - this->minValue);
    update();
}

void CircularProcess::setValue(int value, QString unit1)
{
    setValue((double)value, unit1);
}

void CircularProcess::setAngle(double angle)
{
    this->angle = angle;
    update();
}

void CircularProcess::setPrecision(int precision)
{
    if (precision <= 3) {
        this->precision = precision;
        update();
    }
}

void CircularProcess::setUsedColor(QColor usedColor)
{
    this->usedColor = usedColor;
    update();
}

void CircularProcess::setFreeColor(QColor freeColor)
{
    this->freeColor = freeColor;
    update();
}

void CircularProcess::setRangeTextColor(QColor rangeTextColor)
{
    this->rangeTextColor = rangeTextColor;
    update();
}

void CircularProcess::setValueTextColor(QColor valueTextColor)
{
    this->valueTextColor = valueTextColor;
    update();
}

CircularProcess::~CircularProcess()
{

}

