#include "paintarea.h"

#include <QPainter>
PaintArea::PaintArea(QWidget *parent)
    :QWidget(parent)
{
    setPalette(QPalette(Qt::white)); //设置背景颜色
    setAutoFillBackground(true);//设置自动填充背景色
    setMinimumSize(400,400);//设置窗口最下大小
}
void PaintArea::setShape(Shape s)   //update()更新窗口部件
{
    shape=s;
    update();
}
void PaintArea::setPen(QPen p)
{
    pen=p;
    update();
}
void PaintArea::setBrush(QBrush b)
{
    brush=b;
    update();
}
void PaintArea::setFillRule(Qt::FillRule rule)
{
    fillRule=rule;
    update();
}
//重画事件
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(pen);
    p.setBrush(brush);
    QRect rect(100,100,250,200);//构造一个矩形
    static const QPoint points[4]={
        QPoint(100,100),
        QPoint(200,150),
        QPoint(300,250),
        QPoint(150,300)
    };//确定Points的四个点的坐标
    int startAngle=60*16;
    int spanAngle=180*16;  //为绘制曲线设置参数变量
    QPainterPath path;     //QPainterPath为Qpainter类提供了一个存储容器，里面包含了画的内容和画的顺序，
    path.moveTo(50,150);    //当前位置移动到坐标50,150
    path.lineTo(350,150);   //当前位置开始画直线，终点位置坐标350,150
    path.lineTo(100,325);
    path.lineTo(200,50);
    path.lineTo(300,325);
    path.lineTo(50,150);
    path.setFillRule(fillRule);  //设置填充模式
    switch(shape)
    {
        case Line:       //直线
        p.drawLine(rect.topLeft(),rect.bottomRight());  //绘制直线。起点为矩形左上点，终点为矩形右下点
        break;
        case Rectangle: //长方形
        p.drawRect(rect);
        break;
        case RoundRect:  //圆角方形
        p.drawRoundRect(rect);
        break;
        case Ellipse:   //椭圆形
        p.drawEllipse(rect);
        break;
        case Polygon:   //多边形
        p.drawPolygon(points,4);  //绘制4个顶点多边形
        break;
        case Polyline:  //多边线
        p.drawPolyline(points,4);
        break;
        case Points:    //点
        p.drawPoints(points,4);
        break;
        case Arc:   //弧
        p.drawArc(rect,startAngle,spanAngle);  //后面两个参数分别为 起始角与跨度角
        break;
        case Path:  //绘制之前已经画好的路径
        p.drawPath(path);
        break;
        case Text:  //文字
        p.drawText(rect,Qt::AlignCenter,tr("Hello Qt!"));
        break;
        case Pixmap:    //图片
        p.drawPixmap(150,150,QPixmap("1.png"));//绘制一个图像
        break;
        default:
        break;
    }
}
//前面的椭圆形、直线、长方形、圆角矩形，弧 都是利用矩形为骨架构成的，具体如何构成参照介绍中的绘制函数中的图。
