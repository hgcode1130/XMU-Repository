#include "semicircular.h"

SemiCircular::SemiCircular(QWidget *parent)
    : QWidget(parent)
{

}

void SemiCircular::changeSize(int size)
{
    mySize = size;
}

void SemiCircular::drawOutermostLine(QPainter &painter, int radius)
{
    //保存绘图对象
    painter.save();
    //计算大小圆路径
    QPainterPath outRing;
    QPainterPath inRing;
    outRing.moveTo(0,0);
    inRing.moveTo(0,0);
    //arcTo(矩形，起始角度，旋转角度),创建内切圆，并且确定起始角度
    outRing.arcTo(-radius,-radius, 2*radius,2*radius,0,180);
    //-radius+2,-radius + 2 是以此为坐标点，创建一个高为2*(radius-2)，宽为2*(radius-2)的内切圆
    inRing.addEllipse(-radius+2,-radius+2,2*(radius-2),2*(radius-2));
    outRing.closeSubpath();

    //设置画刷
    painter.setBrush(QColor(54,54,54));
    //大圆减小圆
    painter.drawPath(outRing.subtracted(inRing));
    painter.restore();
}

void SemiCircular::drawGradientArea(QPainter &painter, int radius)
{
    QRect rect(-radius,-radius,2*radius,2*radius);
    QConicalGradient Conical(0,0,0);

    Conical.setColorAt(0.1,QColor(255,34,54));//红色
    Conical.setColorAt(0.2,QColor(222,201,21));//黄色
    Conical.setColorAt(0.3,QColor(28,198,52));//绿色
    Conical.setColorAt(0.5, QColor(61, 79, 255)); //浅蓝色
    painter.setBrush(Conical);
    painter.drawPie(rect,180*16,-(degRotate)*16);
}

void SemiCircular::drawOutMiddleCircle(QPainter &painter, int radius)
{
    painter.save();

    QPainterPath innerRingPath;
    innerRingPath.moveTo(0, 0);
    innerRingPath.arcTo(-radius + 50, -radius + 50, 2 * (radius - 50), 2 * (radius - 50), 180, -180);

    painter.setBrush(QColor(54, 54, 54));

    painter.drawPath(innerRingPath);

    painter.restore();
}

void SemiCircular::drawMiddleLittleCircle(QPainter &painter, int radius)
{
    painter.save();

    // 创建圆锥渐变对象
    QConicalGradient conicalGradient(0, 0, 0); // 中心点和初始角度
    // 设置渐变的颜色关键点
    conicalGradient.setColorAt(0.5, QColor(54, 54, 54));
    conicalGradient.setColorAt(0.1, QColor(68, 68, 68));

    // 创建内圆路径
    QPainterPath inRing;
    inRing.moveTo(0, 0);
    inRing.arcTo(-radius + 50, -radius + 50, 2 * (radius - 50), 2 * (radius - 50), 180, -180);
    inRing.closeSubpath(); // 关闭路径以形成一个完整的形状

    // 应用圆锥渐变
    painter.setBrush(QBrush(conicalGradient));
    // 绘制路径
    painter.drawPath(inRing);

    painter.restore();
}

void SemiCircular::drawMiddleCircle(QPainter &painter, int radius)
{
    painter.save();

    QPainterPath innerRingPath;
    innerRingPath.moveTo(0, 0);
    innerRingPath.arcTo(-radius + 50, -radius + 50, 2 * (radius - 50), 2 * (radius - 50), 180, -180);

    painter.setBrush(QColor(54, 54, 54));

    painter.drawPath(innerRingPath);

    painter.restore();
}

void SemiCircular::drawMiddleBiggestCircle(QPainter &painter, int radius)
{
    painter.save();

    // 创建圆锥渐变对象
    QConicalGradient conicalGradient(0, 0, 0); // 中心点和初始角度
    // 设置渐变的颜色关键点
    conicalGradient.setColorAt(0.1,QColor(255,34,54));//红色
    conicalGradient.setColorAt(0.2,QColor(222,201,21));//黄色
    conicalGradient.setColorAt(0.3,QColor(28,198,52));//绿色
    conicalGradient.setColorAt(0.5, QColor(61, 79, 255)); //浅蓝色

    // 创建内圆路径
    QPainterPath innerRingPath;
    innerRingPath.moveTo(0, 0);
    innerRingPath.arcTo(-radius + 50, -radius + 50, 2 * (radius - 50), 2 * (radius - 50), 180, -180);
    innerRingPath.closeSubpath(); // 关闭路径以形成一个完整的形状

    // 应用圆锥渐变
    painter.setBrush(QBrush(conicalGradient));
    // 绘制路径
    painter.drawPath(innerRingPath);

    painter.restore();
}

void SemiCircular::drawCircle(QPainter &painter, int radius)
{
    painter.save();

    // 定义大圆路径
    QPainterPath outRingPath;
    outRingPath.addEllipse(-radius, -radius, 2 * radius, 2 * radius);

    // 定义小圆路径
    QPainterPath inRingPath;
    inRingPath.addEllipse(-radius + 50, -radius + 50, 2 * (radius - 50), 2 * (radius - 50));

    // 定义并应用上半圆剪切区域
    QPainterPath clipPath;
    clipPath.moveTo(-radius, 0);
    clipPath.arcTo(-radius, -radius, 2 * radius, 2 * radius, 0, 180);
    clipPath.lineTo(radius, 0);
    painter.setClipPath(clipPath);

    // 设置径向渐变并填充大圆
    QRadialGradient radialGradient(0, 0, radius);
    radialGradient.setColorAt(1, QColor(54, 54, 54));
    radialGradient.setColorAt(0.5, Qt::transparent);
    painter.setBrush(radialGradient);
    painter.drawPath(outRingPath);

    // 设置剪切路径以排除小圆区域，从而只在上半圆的环形区域绘制
    painter.setClipPath(inRingPath, Qt::NoClip);
    painter.setBrush(Qt::NoBrush); // 不使用画刷，防止填充小圆
    painter.drawPath(inRingPath); // 实际不绘制，只是清除小圆区域

    painter.restore();
}

void SemiCircular::drawScale(QPainter &painter, int radius)
{
    // 根据控件大小动态调整刻度尺寸
    int scaleLengthSmall = baseSize * 0.01; // 小刻度长度
    int scaleWidthSmall = baseSize * 0.002; // 小刻度宽度
    int scaleLengthBig = baseSize * 0.02; // 大刻度长度
    int scaleWidthBig = baseSize * 0.004; // 大刻度宽度

    QPainterPath pointPath_small;
    pointPath_small.moveTo(-scaleWidthSmall, -scaleWidthSmall);
    pointPath_small.lineTo(scaleWidthSmall, -scaleWidthSmall);
    pointPath_small.lineTo(scaleWidthSmall, scaleLengthSmall);
    pointPath_small.lineTo(-scaleWidthSmall, scaleLengthSmall);

    QPainterPath pointPath_big;
    pointPath_big.moveTo(-scaleWidthBig, -scaleWidthBig);
    pointPath_big.lineTo(scaleWidthBig, -scaleWidthBig);
    pointPath_big.lineTo(scaleWidthBig, scaleLengthBig);
    pointPath_big.lineTo(-scaleWidthBig, scaleLengthBig);


    // 绘制新的小刻度以覆盖0到180度，每1.8度一个小刻度
    for (int i = 0; i <= 100; ++i) {  // 调整循环的范围和步长
        QPointF point(0, 0);
        painter.save();

        // 计算当前角度
        double angle = i * 1.8;
        double radian = qDegreesToRadians(angle);

        // 映射到上半圆
        point.setX(radius * qCos(radian));
        point.setY(-radius * qSin(radian));
        painter.translate(point.x(), point.y());
        painter.rotate(90 - angle);

        painter.setBrush(QColor(255, 255, 255)); // 白色刻度
        if (i % 5 == 0) {
            painter.drawPath(pointPath_big); // 绘制大刻度
        } else {
            painter.drawPath(pointPath_small); // 绘制小刻度
        }

        painter.restore();
    }
}


void SemiCircular::drawNumScale(QPainter &painter, int radius)
{
    painter.setPen(QColor(255, 255, 255));
    // 动态计算字体大小
    int fontSize = max(8, baseSize * 0.016); // 保证最小字体大小为8
    QFont font;
    font.setFamily("Noto Sans CJK SC Regular");
    font.setPointSize(fontSize);
    font.setBold(true);
    painter.setFont(font);

    for (int i = 0; i <= 100; i += 10) {  // 调整循环的范围和步长
        QPointF point(0, 0);
        painter.save();

        // 计算当前角度
        double angle = 180 - i * 1.8;
        double radian = qDegreesToRadians(angle);
        point.setX(radius * qCos(radian));
        point.setY(-radius * qSin(radian)); // 上半圆绘制
        painter.translate(point.x(), point.y());
        painter.rotate(-angle); // 数字垂直

        // 绘制数字
        painter.drawText(-30, 0, 50, 15, Qt::AlignCenter, QString::number(i));

        painter.restore();
    }
    painter.setPen(Qt::NoPen); // 结束绘制时不使用任何笔
}

void SemiCircular::drawUnit(QPainter &painter, int radius)
{
    painter.save();
    painter.setPen(QColor(255,255,255));
    int fontSize = max(8, baseSize * 0.02); // 保证最小字体大小为8
    QFont font;
    font.setFamily("Noto Sans CJK SC Regular");
    font.setPointSize(fontSize);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(-50, -radius - 100, 100, 20,Qt::AlignCenter,QString("℃"));

    painter.setPen(QColor(255,255,255,50));
    painter.restore();
}

void SemiCircular::drawRealTimeData(QPainter &painter, int radius)
{
    painter.save();
    painter.setPen(QColor(255, 255, 255));
    int fontSize = max(8, baseSize * 0.032); // 保证最小字体大小为8
    QFont font;
    font.setFamily("Noto Sans CJK SC Regular");
    font.setPointSize(fontSize);
    font.setBold(true);
    painter.setFont(font);

    QString displayText = QString::number(value) + " ℃";

    painter.drawText(-75, -radius - 80, 150, 100, Qt::AlignCenter, displayText);

    painter.restore();
}


void SemiCircular::drawPointer(QPainter &painter, int baseSize)
{
    int radius = baseSize / 2; // 重新计算半径以适应当前控件大小
    // 定义指针形状的尺寸比例因子
    double pointerTip = 1.8; // 指针尖端相对于半径的比例
    double pointerBaseWidth = 0.04; // 指针底部宽度的比例因子
    double pointerBaseLength = 0.001; // 指针底部长度的比例因子
    double pointerSideLength = 0.001; // 指针侧边长度的比例因子

    QPainterPath pointPath;
    // 指针的尖端
    pointPath.moveTo(0, -radius * pointerTip);
    // 指向尖端右侧的线
    pointPath.lineTo(radius * pointerBaseWidth, -radius + radius * pointerBaseLength);
    // 连接到指针右侧
    pointPath.lineTo(radius * pointerSideLength, -radius * pointerSideLength);
    // 指向尖端左侧的线
    pointPath.lineTo(-radius * pointerBaseWidth, -radius + radius * pointerBaseLength);
    // 完成封闭形状
    pointPath.closeSubpath();

    painter.save();
    // 根据需要旋转指针
    painter.rotate(degRotate - 90);
    // 设置画刷颜色为鲜红色
    painter.setBrush(QColor(255, 34, 54));
    // 绘制指针路径
    painter.drawPath(pointPath);
    painter.restore();
}


void SemiCircular::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height() - 100; // 移动仪表盘的高度，留出一些空间
    baseSize = std::min(width, height); // 使用较小的尺寸作为基数
    const int minRadius = 50; // 示例：最小半径
    int radius = std::max(minRadius, baseSize / 2); // 使用较大值确保最小半径

    // 移动画笔到中下方
    painter.translate(width / 2, height * 0.6);
    // 启用反锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    // 设置画刷颜色
    /* 所有形状绘画 */
    drawCircle(painter, radius - baseSize * 0.0375); // 渐变发光外扇形
    drawGradientArea(painter, radius - baseSize * 0.05); // 动态扇形环
    drawOutMiddleCircle(painter, radius - baseSize * 0.025); // 外中圆
    drawScale(painter, radius - baseSize * 0.1); // 刻度线
    drawNumScale(painter, radius - baseSize * 0.125); // 刻度数字
    drawOutermostLine(painter, radius - baseSize * 0.04375); // 最外细圆线
    drawMiddleBiggestCircle(painter, radius - baseSize * 0.2175); // 中间大圆
    drawMiddleCircle(painter, radius - baseSize * 0.22625); // 中间圆
    drawPointer(painter, radius - baseSize * 0.1625); // 指针
    drawMiddleLittleCircle(painter, radius - baseSize * 0.235); // 中间小圆
    drawRealTimeData(painter, radius - baseSize * 0.50375); //数据
}


SemiCircular::~SemiCircular()
{

}

void SemiCircular::changeValue(int newvalue)
{
    value = newvalue;
    degRotate = static_cast<int>(value * 1.8);
    update(); // 刷新画面
}

