#ifndef PAINTAREA_H
#define PAINTAREA_H



#include <QPaintEvent>


class PaintAreaData;

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    enum Shape{Line,Rectangle,RoundRect,Ellipse,Polygon,Polyline,Points,Arc,Path,Text,
               Pixmap};
    PaintArea(QWidget * parent=0);
    void setShape(Shape);       //设置形状
    void setPen(QPen);          //设置画笔
    void setBrush(QBrush);      //设置画刷
    void setFillRule(Qt::FillRule);//设置填充模式
    void paintEvent(QPaintEvent *);//重画事件
private:
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;
};
#endif // PAINTAREA_H
