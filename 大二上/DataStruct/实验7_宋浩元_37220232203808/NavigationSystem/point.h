#ifndef POINT_H
#define POINT_H

#include <QString>
#include <QPoint>
#include <QDebug>

class Point:public QPoint
{
public:
    Point();
    Point(int x_,int y_);
    Point(QString x_,QString y_,QString next_x_,QString next_y_,QString build_,QString about_,QString name_);
    Point(QString x_,QString y_,QString build_,QString about_,QString name_);
    Point(int x_,int y_,int n_x_,int n_y_);
    QString x;
    QString y;
    QString next_x;
    QString next_y;
    QString build;
    QString name;
    QString about;
    //QString name;
    QString to_string();
    void setX(int x_){x = QString::number(x_);}
    void setY(int y_){y = QString::number(y_);}
    void setXY(int x_,int y_){
        x = QString::number(x_);
        y = QString::number(y_);
    }
    void setAll(Point *p);
    QPoint toQPoint(){
      //  qDebug() << this->to_string();
        return QPoint(x.toInt(),y.toInt());}
    QPoint next_to_point(){
        return QPoint(next_x.toInt(), next_y.toInt());
    }

};
#endif // POINT_H
