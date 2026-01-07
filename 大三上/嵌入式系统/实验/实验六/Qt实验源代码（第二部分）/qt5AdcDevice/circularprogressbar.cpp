#include "circularprogressbar.h"
#include <QPainter>
#include <QDebug>

Circularprogressbar::Circularprogressbar(QWidget *parent) : QWidget(parent),
    outRadis(0),
    inRadis(0),
    side(0),
    value(0),
    valueColor(Qt::green)
{

}

// 设置进度条的数值
void Circularprogressbar::setValue(int value)
{
    this->value = value;  // 更新内部存储的数值
    update();  // 请求重绘组件
}

// 设置进度条的颜色
void Circularprogressbar::setValueColor(const QColor& color)
{
    this->valueColor = color;  // 更新数值的颜色
    update();  // 请求重绘组件
}

// 设置显示的电压值
void Circularprogressbar::setVoltage(int voltage)
{
    this->voltage = voltage;  // 更新电压值
    qDebug() << "voltage:" << voltage;  // 输出电压值到调试控制台
    update();  // 请求重绘组件
}

// 设置显示的电流值
void Circularprogressbar::setCurrent(int current)
{
    this->current = current;  // 更新电流值
    update();  // 请求重绘组件
}


// 绘图事件，用于绘制圆形进度条
void Circularprogressbar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);  // 标记未使用的参数
    int width = this->width();  // 获取组件的宽度
    int height = this->height(); // 获取组件的高度
    int side = qMin(width, height);  // 确定绘制尺寸
    this->outRadis = side / 2;  // 计算外圆半径
    this->inRadis = outRadis - 20;  // 计算内圆半径
    this->side = 3;  // 设置边的宽度
    QPainter painter(this);  // 创建绘图器
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);  // 设置抗锯齿
    painter.translate(width / 2, height / 2);  // 移动绘图原点到组件中心
    painter.scale(side / 200.0, side / 200.0);  // 缩放绘图区域，保证适应大小

    // 调用各个绘制函数
    paintSide(&painter);           // 绘制最外层的边
    paintOutE(&painter);           // 绘制外圆
    paintLine(&painter);           // 绘制刻度线
    paintInE(&painter);            // 绘制内圆
    paintValue(&painter);          // 根据值绘制填充圆弧
    paintInnerCircle(&painter);    // 绘制内部圆圈
    paintBottomCircle(&painter);   // 绘制底部圆圈
}


void Circularprogressbar::paintSide(QPainter *painter)
{
    int radis = outRadis;
    QRect rect(-radis, -radis, radis * 2, radis * 2);
    painter->save();
    painter->setBrush(QBrush(QColor("#505050")));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect);
    painter->restore();
}

void Circularprogressbar::paintOutE(QPainter *painter)
{
    int radis = outRadis - side;
    QRect rect(-radis, -radis, radis * 2, radis * 2);
    painter->save();
    painter->setBrush(QBrush(QColor("#868686")));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect);
    painter->restore();
}

void Circularprogressbar::paintInnerCircle(QPainter *painter)
{
    int innerRadis = inRadis - side;
    QRect rect(-innerRadis, -innerRadis, innerRadis * 2, innerRadis * 2);
    painter->save();
    painter->setBrush(QBrush(QColor("#505050")));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect);
    painter->restore();
}

void Circularprogressbar::paintBottomCircle(QPainter *painter)
{
    int bottomRadis = inRadis - side*13;
    QRect rect(-bottomRadis, -bottomRadis, bottomRadis * 2, bottomRadis * 2);
    painter->save();
    painter->setBrush(QBrush(QColor("#868686")));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect);
    painter->restore();
}


void Circularprogressbar::paintLine(QPainter *painter)
{
    int lineStart = outRadis - 3;
    painter->save();
    painter->setPen(QColor("#868686"));
    int range = 360 / 12;
    for(int i = 0; i < 12; i++){
        painter->rotate(range);
        painter->drawLine(QPoint(lineStart, 0), QPoint(outRadis, 0));
    }
    painter->restore();
}

void Circularprogressbar::paintInE(QPainter *painter)
{
    int radis = inRadis;
    QRect rect(-radis, -radis, radis * 2, radis * 2);
    painter->save();
    painter->setBrush(QBrush(QColor("#646464")));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(rect);
    painter->restore();
}


void Circularprogressbar::paintValue(QPainter *painter)
{
    int oRandis = outRadis - side;
    int rangle = ((double)voltage / 3000) * 360; // 计算最外层圈的填充角度
    int irangle = ((double)current / 500) * 360;

    QRectF rect(-oRandis, -oRandis, oRandis << 1, oRandis << 1);
    QPainterPath path;
    path.arcTo(rect, 270 - rangle, rangle);

    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted((oRandis - inRadis), (oRandis - inRadis), -(oRandis - inRadis), -(oRandis - inRadis)));

    path -= subPath;
    painter->save();
    painter->setBrush(QColor("#00FF00")); // 将第一个圆环填充颜色设置为绿色
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
    painter->restore();

    int innerRadis = inRadis - side;
    QRectF innerRect(-innerRadis, -innerRadis, innerRadis * 2, innerRadis * 2);
    QPainterPath innerPath;
    innerPath.arcTo(innerRect, 270 - irangle, irangle);

    painter->save();
    painter->setBrush(QColor("#0000FF"));
    painter->setPen(Qt::NoPen);
    painter->drawPath(innerPath);
    painter->restore();
}


