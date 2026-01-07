#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include "my_lineedit.h"
#include "syszuxpinyin.h"
#include "newsms.h"
#include "sms.h"
#include <QListWidgetItem>
#include <QMap>
#include <QVector>
#include "ui_mainwindow.h"
#define GET_SIM "AT+CPIN?\r"

namespace Ui {
class MainWindow;
}
class CustomWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sendmessage();
    void recvmessage();
    int serial_select();

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;

    int fd;
    QSerialPort serialPort;
    newsms * mynewsms;
    QMap<QString, sms*> myMap;
    bool Operator; //false 代表电信

private slots:

    void on_pushButton_sendmessage_clicked();
    void myslot();
    void myslotsendnewmsg(QString contact,QString message);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_back_clicked();

signals:
    void mysignalphone(QString,QString);
private:
    Ui::MainWindow *ui;

};

class CustomWidget : public QMainWindow {
  Q_OBJECT
public:
  CustomWidget(QWidget *parent = nullptr): QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
  }

      bool is180 = false;
      bool is0 = false;
      Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
