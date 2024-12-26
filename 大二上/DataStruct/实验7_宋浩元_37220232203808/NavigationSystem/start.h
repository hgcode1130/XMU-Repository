#ifndef START_H
#define START_H

#include "mainwindow.h"
#include "welcom.h"
#include "mysql.h"
#include "login.h"
#include "sigin.h"
#include "libpoint.h"


class Start
{
public:
    Start();
    ~Start();
    void close_welcom();
    void close_mainwindow();
    void set_user(QString name){
        WHO_AM_I->clear();
        WHO_AM_I->append(name);                       }
    QString get_who_am_i(){return *WHO_AM_I;}
    void open_mainwindow();
    void open_login();
    void open_sigin();
    void close_login();
    void close_sigin();
    void setAdmin(bool val){is_admin = val;}
    bool isAdmin(){return is_admin;}
    QWidget *getMainWindow(){return mainwindow;}

    void test();
    LibPoint *LP = NULL;

private:
    QString *WHO_AM_I = new QString("");
    Welcom *welcom ;
    MainWindow *mainwindow;
    Login *login;
    Sigin *sigin;
    bool is_admin = false;
};

#endif // START_H
