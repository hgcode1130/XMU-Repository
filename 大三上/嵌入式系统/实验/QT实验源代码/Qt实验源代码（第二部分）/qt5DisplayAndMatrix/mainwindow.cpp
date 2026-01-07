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

    //获取数字按钮并且连接信号与槽
    for (int i = 0; i < 10; i++) {
        QPushButton* button = customWidget->numKeys->getButton(i);
        connect(button, &QPushButton::clicked, this, [this, i](){
            numberButtonClicked(i);
        });
    }

    connect(customWidget->AButton, &QPushButton::clicked, this, &MainWindow::letterButtonClicked);
    connect(customWidget->BButton, &QPushButton::clicked, this, &MainWindow::letterButtonClicked);
    connect(customWidget->CButton, &QPushButton::clicked, this, &MainWindow::letterButtonClicked);
    connect(customWidget->DButton, &QPushButton::clicked, this, &MainWindow::letterButtonClicked);
    connect(customWidget->EButton, &QPushButton::clicked, this, &MainWindow::letterButtonClicked);
    connect(customWidget->FButton, &QPushButton::clicked, this, &MainWindow::letterButtonClicked);
    connect(customWidget->m_exitButton1, &QPushButton::clicked, this, &MainWindow::buttonexit);

    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    stopGettingValues();
    delete customWidget->Lcd;
    delete customWidget->dm;
}

void MainWindow::stopGettingValues() {
  //如果线程存在则停止获取按键状态线程
  if (customWidget->thread->isRunning()) {
    customWidget->getter->isrunning = false;
    customWidget->thread->quit();
    customWidget->thread->wait();
  }
}

void MainWindow::letterButtonClicked() {
   //获取发送点击信号的按钮对象，使用qobject_cast将按钮对象转换成QPushButton类型
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    char *c_str;
    if (button) {
        //获取按钮显示文本
        QString numberStr = button->text();
        //将QString转换成QByteArray
        QByteArray ba = numberStr.toLatin1();
        //获取QByteArray内存地址,赋值给c字符串指针
        c_str = ba.data();
        //累加按钮文本,显示在LCD上
        customWidget->accumulatedStr += c_str;
        //传递点击字符给设备驱动
        customWidget->dm->trunNewBuf(*c_str);
        //更新LCD显示内容
        customWidget->Lcd->display(customWidget->accumulatedStr);
    }
}

void MainWindow::numberButtonClicked(int num) {
   //获取发送点击信号的按钮对象，使用qobject_cast将按钮对象转换成QPushButton类型
    QPushButton *button = customWidget->numKeys->getButton(num);
    char *c_str;
    if (button) {
        //获取按钮显示文本
        QString numberStr = button->text();
        //将QString转换成QByteArray
        QByteArray ba = numberStr.toLatin1();
        //获取QByteArray内存地址,赋值给c字符串指针
        c_str = ba.data();
        //累加按钮文本,显示在LCD上
        customWidget->accumulatedStr += c_str;
        //传递点击字符给设备驱动
        customWidget->dm->trunNewBuf(*c_str);
        //更新LCD显示内容
        customWidget->Lcd->display(customWidget->accumulatedStr);
    }
}

void MainWindow::buttonexit()
{
    customWidget->getter->isrunning = false;
    if(customWidget->thread->isRunning())
    {
         qDebug()<<"exit";
        customWidget->dm->close();
        customWidget->thread->quit();
    }
    this->close();
    QApplication::quit();
}

