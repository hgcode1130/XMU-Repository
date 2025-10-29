#include "start.h"
#include "mainwindow.h"
#include "welcom.h"
#include "mysql.h"
#include "mymap.h"
#include "main.h"
#include "sigin.h"
#include "libpoint.h"

#include <QDebug>

QString WHO_AM_I = "";
Welcom *welcom ;
MainWindow *mainwindow;



#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtMath>

#define DATABASE_FILE_PATH "MyDataBase.db"




Start::Start()
{
    welcom = new Welcom();
    welcom->show();
    mainwindow = new MainWindow();
    /** test 部分*/
    qDebug() << "start test!";
    LP = new LibPoint();
}

void Start::test(){



}


void Start::close_welcom(){
    qDebug() << "close welcom";
    if (welcom == NULL){
        qDebug() << "welcom NULL";
        qDebug() << "welcom NULL";
        return;
    }
    welcom->hide();
    welcom->close();
}

void Start::close_mainwindow(){
    if (mainwindow == NULL){
        return;
    }
    mainwindow->close();
    free( mainwindow);
}
void Start::open_mainwindow(){
    qDebug() << "start mainwindow";
    if (mainwindow == NULL){
        qDebug() << "main NULL";
        mainwindow = new MainWindow();
    }
    qDebug() << "start MainWindow";
    mainwindow->show();
}

Start::~Start(){
    qDebug() << "Start instruct";
    if (mainwindow != NULL){
        mainwindow->close();
        free(mainwindow);
    }
    if (welcom != NULL){
        welcom->close();
        free(welcom);
    }
}


void Start::open_login(){
    login = new Login();
    Qt::WindowFlags flags = Qt::Dialog;
    login->setWindowFlags(flags);
    login->setWindowModality(Qt::ApplicationModal);
     //将窗口焦点强行聚集在子窗口
    if (login == NULL){
        qDebug() << "NULL";
    }else {
     login->show();
    }

}

void Start::close_login(){

}

void Start::open_sigin(){
    sigin = new Sigin();
    Qt::WindowFlags flags = Qt::Dialog;
    sigin->setWindowFlags(flags);
    sigin->setWindowModality(Qt::ApplicationModal);
    // 将窗口焦点强行聚集在子窗口
    if (sigin == NULL){
        qDebug() << "NULL";
    }else {
        sigin->show();
    }
}
