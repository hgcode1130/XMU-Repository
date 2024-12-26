#include "point.h"
#include <QString>
#include <QtDebug>
#include "mymap.h"
Point::Point()
{

}
Point::Point(int x_,int y_){
    x = QString::number(x_);
    y = QString::number(y_);
    qDebug() << "new Point:" << to_string();
}
Point::Point(QString x_,QString y_,QString build_,QString about_,QString name_){
    x = x_;
    y = y_;
    build = build_;
    about = about_;
    name = name_;
}
Point::Point(int x_,int y_,int n_x_,int n_y_){
    x = QString::number(x_);
    y = QString::number(y_);
    next_x = QString::number(n_x_);
    next_y = QString::number(n_y_);
}
QString Point::to_string(){
    return "{x:" +
            x +
            ",y:" +
            y +
            ",nx:" +
            next_x +
            ",ny:" +
            next_y +
            ",build:" +
            build +
            ",name:" +
            name +
            ",about:" +
            about +
            "}";
}

void Point::setAll(Point *p){
    x = p->x;
    y = p->y;
    build = p->build;
    about = p->about;
    name = p->name;
}
