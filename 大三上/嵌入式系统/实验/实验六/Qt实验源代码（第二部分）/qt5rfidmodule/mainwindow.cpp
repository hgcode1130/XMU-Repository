#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    customWidget = new CustomWidget();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    customWidget->resize(screenWidth, screenHeight);
    customWidget->showFullScreen();

    //取消滑动条
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    proxyWidget = scene->addWidget(customWidget);
    proxyWidget->setTransformOriginPoint(proxyWidget->boundingRect().center());
    proxyWidget->setZValue(100);

    //开启线程进行三轴检测
    lis3dh = new Lis3dhDevice();
    thread3dh = new QThread();
    lis3dh->moveToThread(thread3dh);
    thread3dh->start();
    connect(thread3dh, &QThread::started, lis3dh, &Lis3dhDevice::run);
    connect(lis3dh, &Lis3dhDevice::stopthread, [&](){
        if(thread3dh->isRunning()){
            lis3dh->changeRunningState(false);
            thread3dh->quit();
        }
    });
    connect(lis3dh, &Lis3dhDevice::change180, [&](){
        if(!customWidget->is180){
            qDebug()<<"turn 180";
            this->view->rotate(180);
            update();
            customWidget->is180 = true;
            customWidget->is0 = true;
        }
    });
    connect(lis3dh, &Lis3dhDevice::change0, [&](){
        if(customWidget->is0){
            qDebug()<<"turn 0";
            this->view->rotate(180);
            update();
            customWidget->is180 = false;
            customWidget->is0 = false;
        }
    });

    connect(customWidget->mainwidget,&QTabWidget::currentChanged,this,&MainWindow::tabChange);
    connect(customWidget->mytimer,&QTimer::timeout,this,&MainWindow::modeChange);
    connect(customWidget->exit,&QPushButton::clicked,this,&MainWindow::myslot_exit);

    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete lis3dh;
    delete thread3dh;
    delete customWidget;
    delete ui;
}


void MainWindow::change_hf(QString hf)
{
    customWidget->Hflabel->setText("卡号:" + hf);  // 更新界面中高频页的标签显示读取到的卡号
}

void MainWindow::change_lf(QString lf)
{
    customWidget->Lflabel->setText("卡号:" + lf);  // 更新界面中低频页的标签显示读取到的卡号
}

void MainWindow::change_nfc(QString nfc)
{
    customWidget->NFClabel->setText("卡号:" + nfc);  // 更新界面中 NFC 页的标签显示读取到的卡号
}

void MainWindow::change_915m(QString f915m)
{
    customWidget->F915Mlabel->setText("卡号:" + f915m);  // 更新界面中 915m 页的标签显示读取到的卡号
}

void MainWindow::change_2_4g(QString f2_4g)
{
    customWidget->NFClabel->setText("卡号:" + f2_4g);  // 更新界面中 2_4g 页的标签显示读取到的卡号
}

void MainWindow::modeChange()
{
    int index = customWidget->mainwidget->currentIndex();  // 获取当前选中的标签页索引
    QString rfidData;
    switch (index) {
    case 0:
        rfidData = customWidget->rfid->readHf();
        if (rfidData != "00 00 00 00" && !rfidData.isEmpty()) {
            change_hf(rfidData);
        }
        break;
    case 1:
        rfidData = customWidget->rfid->readLf();
        if (rfidData != "00 00 00 00 00" && !rfidData.isEmpty()) {
            change_lf(rfidData);
        }
        break;
    case 2:
        rfidData = customWidget->rfid->read915M();
        if (rfidData != "00 00 00 00" && !rfidData.isEmpty()) {
            change_915m(rfidData);
        }
        break;
    case 3:
        rfidData = customWidget->rfid->readNfc();
        if (rfidData != "00 00 00 00" && !rfidData.isEmpty()) {
            change_nfc(rfidData);
        }
        break;
    case 4:
        rfidData = customWidget->rfid->read2_4G();
        if (rfidData != "00 00 00 00" && !rfidData.isEmpty()) {
            change_2_4g(rfidData);
        }
        break;
    default:
        break;
    }
}

void MainWindow::tabChange(int index)
{
    QThread::usleep(100);
    switch (index) {
    case 0:
        customWidget->mytimer->start(100);
        break;
    case 1:
        customWidget->mytimer->start(1700);
        break;
    default:
        customWidget->mytimer->start(2000);
        break;
    }
    customWidget->rfid->closeRfid();
    customWidget->rfid->func_init(index);
}


void MainWindow::myslot_exit()
{
    this->close();  // 关闭窗口
    QApplication::quit();  // 退出应用程序
}


