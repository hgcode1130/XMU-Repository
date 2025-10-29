#include "mysql.h"
#include "base.h"
#include "point.h"
#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include "mymap.h"
//#define DATABASE_FILE_PATH ":/sql/src/MyDataBase.db"
#define DATABASE_FILE_PATH "MyDataBase.db"
#ifndef RANGE
#define RANGE 8
#endif

MySQL::MySQL() {
    static QSqlDatabase db;

    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");
        db.setDatabaseName(DATABASE_FILE_PATH);

        // 如果数据库文件不存在，则从资源中复制
        QFileInfo file(DATABASE_FILE_PATH);
        if (!file.exists()) {
            QFile resourceFile(":/sql/src/MyDataBase.db");
            if (!resourceFile.exists()) {
                qCritical() << "Error: Resource database file does not exist!";
                return;
            }
            if (!resourceFile.copy(DATABASE_FILE_PATH)) {
                qCritical() << "Error: Failed to copy database file to" << DATABASE_FILE_PATH;
                return;
            }
            QFile copiedFile(DATABASE_FILE_PATH);
            copiedFile.setPermissions(QFile::ReadOwner | QFile::WriteOwner);
            qDebug() << "Database file copied to" << DATABASE_FILE_PATH;
        }

        // 打开数据库
        if (!db.open()) {
            qCritical() << "Error: Failed to open database at" << DATABASE_FILE_PATH
                        << "Error:" << db.lastError();
            return;
        }
    }

    database = db; // 保存到成员变量
    qDebug() << "Succeed to connect to database.";
}



void MySQL::init(){
    QFile file(":/sql/src/POINT.sql");



   // QSqlDatabase database;
    database.setDatabaseName(DATABASE_FILE_PATH);
    if (!database.isOpen() && !database.open())
    {
        qDebug() << "Error: When init, Failed to connect database." << database.lastError();
        return;
       // QMessageBox::about(this, "tip", "数据库创建失败！");
    }
    else
    {
        qDebug() << "(init)Succeed to connect database." ;

    }

    //创建表格
    QSqlQuery sql_query;
    if(!sql_query.exec("create table USERS("
                       "username text primary key, "
                       "passwd text,"
                       "admin int DEFAULT 0)"))
    {
        qDebug() << "Error: (init)Fail to create USERS table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "(init)Table USERS created!";
    }
    if(!sql_query.exec("create table POINT("
                       "point text primary key,"
                       "x int, "
                       "y int, "
                       "build int DEFAULT 0,"
                       "buiding_name text,"
                       "about text)") ||
            !sql_query.exec("create table NEAR("
                            "x int, "
                            "y int, "
                            "next_x int,"
                            "next_y int,"
                            "int dis)"))
    {
        qDebug() << "Error: (init)Fail to create POINT table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "(init)Table POINT created!";
    }
    add_user("admin","admin","1");
}

void MySQL::clearAllPoints() {
    if (!database.open()) {
        qDebug() << "Error: 数据库未打开！";
        return;
    }

    QSqlQuery sql_query;

    // 删除 POINT 表中的所有数据
    QString clearPointsSql = "DELETE FROM POINT;";
    if (!sql_query.exec(clearPointsSql)) {
        qDebug() << "清空 POINT 表失败：" << sql_query.lastError();
    } else {
        qDebug() << "成功清空 POINT 表！";
    }

    // 删除 NEAR 表中的所有数据
    QString clearNearSql = "DELETE FROM NEAR;";
    if (!sql_query.exec(clearNearSql)) {
        qDebug() << "清空 NEAR 表失败：" << sql_query.lastError();
    } else {
        qDebug() << "成功清空 NEAR 表！";
    }
}

QVector<Point> MySQL::get_min_dis_point(int x,int y){
    QVector<Point> retval;
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
    }
    QString sql = "SELECT next_x,next_y,min(dis) FROM NEAR where x = " + QString::number(x) + " and y = " + QString::number(y) + ";";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找失败" << sql_query.lastError();
        qDebug() << sql;
    }
    if (sql_query.next()) {
        retval.append(Point(sql_query.value(0).toInt(),sql_query.value(1).toInt()));
    }
    return retval;
}


void MySQL::inser_near(int x, int y, int next_x, int next_y) {
    if (!database.open()) {
        qDebug() << "Error: 数据库未打开！";
        return;
    }
    QSqlQuery sql_query;

    // 检查连接是否已存在
    QString checkSql = QString(
                           "SELECT COUNT(*) FROM NEAR WHERE x = %1 AND y = %2 AND next_x = %3 AND next_y = %4;")
                           .arg(x)
                           .arg(y)
                           .arg(next_x)
                           .arg(next_y);
    if (sql_query.exec(checkSql) && sql_query.next() && sql_query.value(0).toInt() > 0) {
        qDebug() << "连接已存在，跳过插入：(" << x << ", " << y << ") -> (" << next_x << ", " << next_y << ")";
        return;
    }

    // 插入连接
    QString sql = QString(
                      "INSERT INTO NEAR (x, y, next_x, next_y, dis) "
                      "VALUES (%1, %2, %3, %4, %5);")
                      .arg(x)
                      .arg(y)
                      .arg(next_x)
                      .arg(next_y)
                      .arg(get_dis(x, y, next_x, next_y));
    if (sql_query.exec(sql)) {
        qDebug() << "成功插入连接：(" << x << ", " << y << ") -> (" << next_x << ", " << next_y << ")";
    } else {
        qDebug() << "插入连接失败：" << sql_query.lastError() << "\nSQL: " << sql;
    }
}

bool MySQL::add_user(QString name, QString passwd, QString is_admin){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
        return  false;
    }
    QSqlQuery sql_query ;
    QString sql = "INSERT INTO USERS(username,passwd,admin)"
                  "VALUES(\'" + name + "\',\'" + passwd + "\'," + is_admin + ")";
    if (sql_query.exec(sql)){
        qDebug() << "Add user Successfully!";
        return true;
    }else {
        qDebug() << "Error:Add user Failure! sql_string:" + sql;
    }
    return false;
}

QString MySQL::get_user_passwd(QString username){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
    }
    QString sql = "SELECT passwd FROM USERS where username = \'" + username + "\';";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找失败" << sql_query.lastError();
        return sql_query.value(0).toString();
    }
    if (sql_query.next()) {
        qDebug() << "查找用户：" << username << ",passwd:" << sql_query.value(0).toString();
        return sql_query.value(0).toString();
    }
    return "";
}

MySQL::~MySQL() {
    // 不主动关闭默认连接，交由应用程序退出时统一管理
    if (database.isOpen() && database.connectionName() != "qt_sql_default_connection") {
        database.close();
        qDebug() << "Database closed;";
    } else {
        qDebug() << "Skipping database close for default connection.";
    }
}



void MySQL::inser_point(Point *P){
    if (!database.open()) {
        qDebug() << "Error: 数据库未打开！";
        return;
    }
    QSqlQuery sql_query;

    // 检查点是否已经存在
    QString checkSql = QString(
                           "SELECT COUNT(*) FROM POINT WHERE x = %1 AND y = %2;")
                           .arg(P->x.toInt())
                           .arg(P->y.toInt());
    if (sql_query.exec(checkSql) && sql_query.next() && sql_query.value(0).toInt() > 0) {
        qDebug() << "点已存在，跳过插入：" << P->to_string();
        return;
    }

    // 如果不存在则插入点
    QString sql = QString(
                      "INSERT INTO POINT (point, x, y, build, buiding_name, about) "
                      "VALUES ('{%1, %2}', %1, %2, %3, '%4', '%5');")
                      .arg(P->x.toInt())
                      .arg(P->y.toInt())
                      .arg(P->build.toInt())
                      .arg(P->name)
                      .arg(P->about);
    if (sql_query.exec(sql)) {
        qDebug() << "成功插入点：" << P->to_string();
    } else {
        qDebug() << "插入点失败：" << sql_query.lastError() << "\nSQL: " << sql;
    }
}

void MySQL::remove_point_by_XY(int x, int y){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
       // QMessageBox::about(this, "tip", "数据库链接失败！");
        return ;
    }
    QString sql = " DELETE from POINT where x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " ;";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "删除点失败" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
    sql = " DELETE from NEAR where ( x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " )  or (next_x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and next_y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " ) ";
    if (!sql_query.exec(sql)){
        qDebug() << "删除点失败" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
}
void MySQL::get_point_by_XY(Point** p,int x,int y){
    if (!database.isOpen()) {
        if (!database.open()) {
            qDebug() << "Error: Database is not open!";
            return;
        }
    }
    if (p == NULL){return ;}
    if(*p != NULL){
        delete *p;
        *p = NULL;
    }

     qDebug() << "Querying point near (" << x << ", " << y << ")";
    QString sql = " SELECT * FROM POINT where x between " +
            QString::number(x - RANGE) +
            " and " +
            QString::number(x + RANGE) +
            " and y between " +
            QString::number(y - RANGE) +
            " and " +
            QString::number(y + RANGE) +
            " ;";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找点失败" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
    if (sql_query.next()) {
        Point *tep = new Point();
        tep->x = sql_query.value(1).toString();
        tep->y = sql_query.value(2).toString();
        tep->build = sql_query.value(3).toString();
        tep->name = sql_query.value(4).toString();
        tep->about = sql_query.value(5).toString();
        qDebug() << "find + 1";
        qDebug() << tep->to_string();
        *p = tep;
        qDebug() << "Point found:" << (*p)->to_string();
        return ;
    }
    return;
}

QVector<Point> MySQL::find_point(int x,int y){
    qDebug() << "finding point:" << x <<y;
            if (!database.open()){
                qDebug() << "Error:数据库已关闭！";
                return {};
            }
            QVector<Point> retval = QVector<Point>();
            QString sql = " SELECT * FROM POINT where x between " +
                    QString::number(x - RANGE) +
                    " and " +
                    QString::number(x + RANGE) +
                    " and y between " +
                    QString::number(y - RANGE) +
                    " and " +
                    QString::number(y + RANGE) +
                    ";";
            QSqlQuery sql_query;
            if (!sql_query.exec(sql)){
                qDebug() << "查找点失败" << sql_query.lastError();
                qDebug() << "sql:" << sql;
                return retval;
            }
            while (sql_query.next()) {
                Point tep;
                tep.x = sql_query.value(1).toString();
                tep.y = sql_query.value(2).toString();
                tep.build = sql_query.value(3).toString();
                tep.name = sql_query.value(4).toString();
                tep.about = sql_query.value(5).toString();
                retval.append(tep);
                qDebug() << "find + 1";
                qDebug() << tep.to_string();
            }
            return retval;
}
Point MySQL::find_exact_point(int x,int y){
    return Point(x,y);
}
QVector<Point> MySQL::getAllLines(){
            if (!database.open()){
                qDebug() << "Error:数据库已关闭！";
                return {};
            }
            QVector<Point> retval = QVector<Point>();
            QString sql = " SELECT * FROM NEAR ;";
            QSqlQuery sql_query;
            if (!sql_query.exec(sql)){
                return retval;
            }
            while (sql_query.next()) {
                Point tep;
                tep.x = sql_query.value(0).toString();
                tep.y = sql_query.value(1).toString();
                tep.next_x = sql_query.value(2).toString();
                tep.next_y = sql_query.value(3).toString();
                retval.append(tep);
            }
            return retval;
}

QVector<Point> MySQL::getAllPoints(){
    qDebug() << "finding points";
            if (!database.open()){
                qDebug() << "Error:数据库已关闭！";
                return {};
            }
            QVector<Point> retval = QVector<Point>();
            QString sql = " SELECT * FROM POINT ;";
            QSqlQuery sql_query;
            if (!sql_query.exec(sql)){
                qDebug() << "查找点失败" << sql_query.lastError();
                qDebug() << "sql:" << sql;
                return retval;
            }
            while (sql_query.next()) {
                Point tep;
                tep.x = sql_query.value(1).toString();
                tep.y = sql_query.value(2).toString();
                tep.build = sql_query.value(3).toString();
                tep.name = sql_query.value(4).toString();
                tep.about = sql_query.value(5).toString();
                retval.append(tep);
                qDebug() << "find + 1";
                qDebug() << tep.to_string();
            }
            return retval;
}

QString MySQL::get_admin_name(){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
    }
    QString sql = "SELECT username FROM USERS where admin = 1";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "查找失败" << sql_query.lastError();
        return  "_error_error_";
    }
    if (sql_query.next()) {
        return sql_query.value(0).toString();
    }
    return "_error_error_";
}

void MySQL::update(QString x,QString y,QString is_build,QString about,QString name){
    if (!database.open()){
        qDebug() << "Error:数据库已关闭！";
        return ;
    }
    QString sql = "update POINT set build = '" + is_build + "',buiding_name = '" + name + "',about = '" + about + "' where x = " +
            x +
            " and y = " +
            y +
            " ;";
    QSqlQuery sql_query;
    if (!sql_query.exec(sql)){
        qDebug() << "ERROR:uopdated failure!" << sql_query.lastError();
        qDebug() << "sql:" << sql;
        return;
    }
}
