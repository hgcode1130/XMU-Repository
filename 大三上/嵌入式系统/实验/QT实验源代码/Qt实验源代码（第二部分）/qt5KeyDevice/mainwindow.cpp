#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    customWidget->topLabel->raise();

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

    QThread *thread = new QThread();
    customWidget->key->moveToThread(thread);

    //连接按钮的信号和槽函数
    connect(thread,&QThread::started,customWidget->key,&KeyDevice::getKeys);
    connect(customWidget->key,&KeyDevice::KeysState,this,&MainWindow::changeKey);
    connect(customWidget->m_exitButton1,&QPushButton::clicked, this, &MainWindow::on_exit_clicked);
    thread->start();

    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}

void MainWindow::on_exit_clicked()
{
    delete customWidget->key;
    qDebug()<<"exit";
    this->close();
    QApplication::quit();
}

//根据获取到的keysState判断哪个按钮被按下
void MainWindow::changeKey(int keyStates)
{
    QPixmap keyPixmapOff(":/icon/Key_off.png");
    keyPixmapOff = keyPixmapOff.scaled(200,106);

    QPixmap keyPixmapOn(":/icon/Key_on.png");
    keyPixmapOn = keyPixmapOn.scaled(200,106);

    switch (keyStates) {
    case KEY1_ON:
        customWidget->Key1->setPixmap(keyPixmapOn);
        customWidget->Key1Text->setText("Key1被按下");
        break;
    case KEY1_OFF:
        customWidget->Key1->setPixmap(keyPixmapOff);
        customWidget->Key1Text->setText("Key1未被按下");
        break;
    case KEY2_ON:
        customWidget->Key2->setPixmap(keyPixmapOn);
        customWidget->Key2Text->setText("Key2被按下");
        break;
    case KEY2_OFF:
        customWidget->Key2->setPixmap(keyPixmapOff);
        customWidget->Key2Text->setText("Key2未被按下");
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

