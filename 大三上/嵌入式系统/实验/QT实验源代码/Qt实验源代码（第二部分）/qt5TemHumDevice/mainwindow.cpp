#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    customWidget->topLabel->raise();

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

    customWidget->myThread = new QThread();
    customWidget->tem->moveToThread(customWidget->myThread);
    // 连接按钮的信号和槽函数
    connect(customWidget->ExitButton, &QPushButton::clicked, this ,&MainWindow::on_exit_clicked);
    connect(customWidget->myThread, &QThread::started, customWidget->tem ,&temDevice::readData);
    connect(customWidget->tem, &temDevice::sendData, this ,&MainWindow::updateTem);
    customWidget->myThread->start();
    if(customWidget->myThread->isRunning()){qDebug()<<"start";}else{qDebug()<<"start failed";}
    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}

void MainWindow::updateTem(float data)
{
    customWidget->round1->setValue(data,"℃");
    customWidget->temSeries->append(customWidget->x, data);
    customWidget->x++;

    // 每次更新数据时，判断是否需要滚动图表
    if (customWidget->x >= 10) {
        customWidget->chart->scroll(1, 0);
        customWidget->axisX->setRange(customWidget->x - 9, customWidget->x);
    }
}
void MainWindow::on_exit_clicked()
{
    delete customWidget->tem;
    this->close();
    QApplication::quit();
}

MainWindow::~MainWindow()
{
    delete timer;
    delete temhum;
    delete chart;
    delete ExitButton;
    delete round1;
}
