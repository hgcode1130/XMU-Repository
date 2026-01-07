#include "widget.h"

Widget::Widget(QWidget *parent)
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

   connect(customWidget->topexit,&QPushButton::clicked,this,&Widget::exitSlot);
   connect(customWidget->round1,&CircularProcess::angleChanged,this,&Widget::trunServo);

   connect(customWidget->fanBackButton,&QPushButton::clicked,this,&Widget::backSlot);
   connect(customWidget->fanStopButton,&QPushButton::clicked,this,&Widget::stopFanSlot);
   connect(customWidget->fanButton,&QPushButton::clicked,this,&Widget::fanButtonSlot);
   connect(customWidget->timer,SIGNAL(timeout()),customWidget->fan,SLOT(update()));
   connect(this, SIGNAL(Set0()), customWidget->fan, SLOT(setPart0()));
   connect(this, SIGNAL(Set1()), customWidget->fan, SLOT(setPart1()));
   connect(this, SIGNAL(Set2()), customWidget->fan, SLOT(setPart2()));

    connect(customWidget->thread,&QThread::started,customWidget->stepper,&stepperDevice::run);
    connect(customWidget->thread,&QThread::finished,this,[=](){
        customWidget->stepper->isrun = false;
    });

    foreach(QObject *obj, customWidget->Page3->children()) {
        QPushButton *button = qobject_cast<QPushButton*>(obj);
        if(button)
        if (button && button->objectName().startsWith("part")) {
            QString buttonName = button->objectName();
            int partIndex = buttonName.mid(4).toInt();

            connect(button, &QPushButton::clicked, this, [&, partIndex]() {
                if (partIndex != 0 && !customWidget->thread->isRunning()) {
                    customWidget->thread->start();
                }else if(partIndex == 0 && customWidget->thread->isRunning()){
                    customWidget->thread->quit();
                }
                customWidget->stepper->setPart(partIndex);
            });
        }
    }

    connect(customWidget,&CustomWidget::currentChanged,this,&Widget::handleIndexChange);
    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}


Widget::~Widget()
{

}

void Widget::handleIndexChange(int index)
{
   emit Set0();

    // 关闭所有设备，以准备切换到新的标签页
   customWidget->servo->closeServo(); // 关闭舵机设备
   customWidget->dc->closeDc();// 关闭直流电机设备
   customWidget->stepper->closeStepper();// 关闭步进电机设备

   // 如果步进电机的控制线程正在运行，则请求退出线程
   if(customWidget->thread->isRunning())
   {
       customWidget->thread->quit();
   }

   // 根据当前选中的标签页索引，初始化相应的设备
    switch (index) {
    case 0:
        customWidget->servo->initServo();// 初始化舵机设备
        customWidget->servo->steerServo(customWidget->round1->outPutPrecent);// 设置舵机到指定角度
        break;
    case 1:
        customWidget->dc->initDc();// 初始化直流电机设备
        break;
    case 2:
        // 如果步进电机的控制线程未在运行，则启动线程
        if(!customWidget->thread->isRunning())
        {
            customWidget->thread->start();
        }
        customWidget->stepper->initstepper();// 初始化步进电机设备
        break;
    default:
        break;
    }
}

void Widget::trunServo(int percent)
{
    customWidget->servo->steerServo(percent);
}

void Widget::backSlot()
{
    emit Set2();
    customWidget->dc->controlDc(1);
}

void Widget::stopFanSlot()
{
    emit Set0();
    customWidget->dc->controlDc(2);
}

void Widget::fanButtonSlot()
{
    emit Set1();
    customWidget->dc->controlDc(0);
}

void Widget::exitSlot()
{
    customWidget->servo->closeServo();
    customWidget->dc->closeDc();
    customWidget->stepper->closeStepper();
    delete customWidget->servo;
    delete customWidget->dc;
    delete customWidget->stepper;
    this->close();
    QApplication::quit();
}

