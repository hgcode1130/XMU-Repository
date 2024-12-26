#ifndef MYSQL_H
#define MYSQL_H
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <vector>
#include <QVector>

#include "point.h"
class MySQL
{

public:
    QSqlDatabase database;
    static MySQL& getInstance() {
        static MySQL instance;
        return instance;
    }

    QSqlDatabase& getDatabase() {
        return database;
    }
    MySQL();
    ~MySQL();
     void init();
     bool add_user(QString name,QString passwd,QString is_admin);
     QVector<Point> get_min_dis_point(int x,int y);
     QString get_user_passwd(QString username);
     void inser_point(Point *P);
     void remove_point_by_XY(int x,int y);
     QVector<Point> find_point(int x,int y);
     Point find_exact_point(int x,int y);
     QVector<Point> getAllPoints();
     QVector<Point> getAllLines();
     QString get_admin_name();
     void get_point_by_XY(Point** p,int x,int y);
     void update(QString x,QString y,QString is_build,QString about,QString name);
     void inser_near(int x,int y,int next_x,int next_y);
     //Point test(){return (Point)NULL;}
     void clearAllPoints();

};

#endif // MYSQL_H
