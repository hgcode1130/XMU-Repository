#include "circularprocess.h"
#include <QPushButton>
CircularProcess::CircularProcess(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet("background-color: #d4d4d4;");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start(1000);

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    setPalette(palette);

    minValue = 0;
    maxValue = 180;
    value = 0;
    precision = 0;

    unit = "";

    currentPercent = 0;
    valuePercent = 0;

    freeColor = QColor(215, 215, 215);
}

void CircularProcess::mousePressEvent(QMouseEvent *event) {
    updateValueFromMouseEvent(event);
}

void CircularProcess::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        updateValueFromMouseEvent(event);
    }
}

void CircularProcess::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit angleChanged(sendpercent);
    }
}


void CircularProcess::updateValueFromMouseEvent(QMouseEvent *event) {
    int dx = event->pos().x() - width() / 2;
    int dy = event->pos().y() - height() / 2;
    double angle = atan2(-dy, dx) * 180 / M_PI;

    if (angle < 0) {
        angle += 360;
    }

    // 反转角度增长方向
    if (angle > 180) {
      //  angle = 360 - angle;
        return;
    }

    angle = 180 - angle;
    sendpercent = angle;
    outPutPrecent = angle;
    int trunpercen = 0;
    trunpercen = (angle / 180.0) * 100;
    setValueFromPercent(trunpercen);
}

void CircularProcess::setValueFromPercent(double percent) {
    double newValue = minValue + (maxValue - minValue) * (percent / 100.0);
    setValue(newValue, unit);
}

void CircularProcess::paintEvent(QPaintEvent *) {
    int width = this->width();
    int height = this->height();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width / 2, height / 2);
    int side = qMin(width, height);

    // 定义一个圆形路径
    QPainterPath path;
    path.addEllipse(-side / 2, -side / 2, side, side);

    // 应用圆形路径为裁剪路径
    painter.setClipPath(path);

    // 进一步限制裁剪区域到上半部分
    QRect clipRect(-side / 2, -side / 2, side, side / 2);
    painter.setClipRect(clipRect, Qt::IntersectClip);

    painter.scale(side / 200.0, side / 200.0);

    // 注意调整背景填充和其他绘图命令，确保它们适应新的裁剪区域
    painter.fillRect(-100, -50, 200, 100, palette().color(QPalette::Background));
    drawDial(&painter);
    drawText(&painter, unit);
}

void CircularProcess::drawDial(QPainter *painter) {
    int radius = 100;
    double lineWidth = 2.5;
    painter->save();

    setDialusedColor(currentPercent);
    double rotate = 180.0 / 100;

    int startAngle = 90;
    for (double i = 0; i < 100; i++) {
        if(i < currentPercent) {
            painter->setPen(QPen(usedColor, lineWidth));
        } else {
            painter->setPen(QPen(freeColor, lineWidth));
        }
        double currentAngle = startAngle + i * rotate;
        painter->save();
        painter->rotate(currentAngle);
        painter->drawLine(0, radius, 0, radius / 1.2);
        painter->restore();
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

void CircularProcess::drawText(QPainter *painter, QString unit) {
    painter->save();
    double currentValue = currentPercent * ((maxValue - minValue) / 100) + minValue;
    if (currentValue > value) {
        currentValue = value;
    }
    QString strValue = QString("%1°%2").arg(QString::number(currentValue, 'f', precision)).arg(unit);
    // 绘制当前值
    painter->setFont(QFont("Noto Sans CJK SC Regular", 10));
    painter->setPen(QPen(valueTextColor));
    QFontMetricsF fm = QFontMetricsF(painter->font());

    int centerX = 0;
    int centerY = 0;

    QSizeF textSize = fm.size(Qt::TextSingleLine, strValue);

    int textX = centerX - textSize.width() / 2;
    int textY = centerY + textSize.height() / 35;

    painter->drawText(textX, textY, strValue);
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

