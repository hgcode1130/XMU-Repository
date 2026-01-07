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

      connect(customWidget->adc,&mixAdcDevice::sendData,this,&Widget::recvData);
      connect(customWidget->exitButton,&QPushButton::clicked,this,&Widget::exitBtnClicked);
      connect(customWidget,&CustomWidget::currentChanged,this,&Widget::handleIndexChange);
      connect(customWidget->tem,&temDevice::sendData,this,&Widget::updateCircular);
      connect(customWidget->relayButton,&QPushButton::clicked,this,&Widget::relayButtonClicked);
      connect(customWidget->light,&lightElectric::sendState,this,&Widget::handleLightElectricState);
      connect(customWidget->beepBtn,&QPushButton::clicked,this,&Widget::beepBtnClicked);

    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}


/***在析构函数关闭所有节点***/
Widget::~Widget()
{
    customWidget->adc->closeAdcFd();
    delete customWidget->adc;
    customWidget->tem->closeTemFd();
    delete customWidget->tem;
    customWidget->relay->closeRelayFd();
    delete customWidget->relay;
    customWidget->light->closeLightElectric();
    delete customWidget->light;
}


/***当前页面发生改变的时候会调用这个槽函数
根据当前处于的不同页面决定开启不同的线程***/

void Widget::handleIndexChange(int index) {
    // 停止所有设备操作
 //   qDebug()<<"handleIndexChange";
    customWidget->adc->changeThreadState(false);
    customWidget->tem->changeThreadState(false);
    customWidget->light->changeLightState(false);
    customWidget->adc->closeAdcFd();
    customWidget->tem->closeTemFd();

    // 根据选定的索引启动对应设备
    switch (index) {
        case 0: // 酒精
        case 1: // 可燃气
        case 5: // 火焰
        case 7:
        customWidget->threadPool->waitForDone();
        customWidget->adc->changeThreadState(false);
        customWidget->adc->closeAdcFd();
        //customWidget->adc->changeThreadState(true);
        customWidget->threadPool->start(new ReadAdcDataTask(customWidget->adc,index == 0 ? "A" : (index == 1 ? "S" : (index == 5 ? "F" : "L"))));
        break;
    case 2: // 温度
        //customWidget->tem->openTemDevice();
        customWidget->tem->changeThreadState(true);
        customWidget->threadPool->start(new ReadTemDataTask(customWidget->tem));
        break;
    case 4: // 光电
        customWidget->light->changeLightState(true);
        customWidget->threadPool->start(new ReadLightStateTask(customWidget->light));
        break;
        default:
            break;
    }
}

/***接收adc传来的数据根据所在不同的页面更新对应的控件***/
void Widget::recvData(int data)
{
    int index = customWidget->currentIndex();

    switch (index) {
    case 0:
        updateAlcoholLedState(data);
        break;
    case 1:
        updateSeries(data);
        break;
    case 5:
        updateFrameState(data);
        break;
    case 7:
        updateLightLCD(data);
        break;
    default:
        break;
    }
}

/***根据传递过来的数据更新图表，当点数大于9的时候清掉前面的点***/
void Widget::updateSeries(int data)
{
    if(customWidget->count > 10){
        customWidget->chart->scroll(1,0);
        customWidget->chart->axisX()->setRange(customWidget->count -9,customWidget->count);
    }
    customWidget->gasSeries->append(customWidget->count,data);
    customWidget->count++;
}

/***更新温度仪表盘***/
void Widget::updateCircular(float data)
{
    int updateData = static_cast<int>(data);
    customWidget->temCircular->changeValue(updateData);
}

//处理蜂鸣器播放
void Widget::beepBtnClicked()
{
    if(!customWidget->isBeepOn){
        customWidget->beep->changeBeepState(1);
        customWidget->isBeepOn = true;
        customWidget->beepBtn->setIcon(QIcon(":/icon/icon/beepmax.png"));
        customWidget->beepBtn->setIconSize(QSize(300, 300));
    }else{
        customWidget->beep->changeBeepState(0);
        customWidget->isBeepOn = false;
        customWidget->beepBtn->setIcon(QIcon(":/icon/icon/beepoff.png"));
        customWidget->beepBtn->setIconSize(QSize(300, 300));
    }
}

void Widget::exitBtnClicked()
{
    customWidget->beep->closeBeepFd();
    this->close();
    QApplication::quit();
}

/***更新指示灯颜色***/
void Widget::updateAlcoholLedState(int data)
{
  //  qDebug()<<"Alcoholdata"<<data;
    if(data > 140){
        customWidget->Alcohol->setLedColor("red");
        customWidget->alcoholText->setText("酒精浓度超标");
    }else{
        customWidget->Alcohol->setLedColor("green");
        customWidget->alcoholText->setText("酒精浓度未超标");
    }
}

/***根据传递的值判断是否开启动图***/
void Widget::updateFrameState(int data)
{
  //  qDebug()<<"Framedata"<<data;
    if(data > 600){
      customWidget->frameLabel->setMovie(customWidget->frameMovie);
      customWidget->frameMovie->start();
      customWidget->frameLabelText->setText("检测到火焰");
    }else{
        customWidget->frameMovie->stop();
        QPixmap frameoffPixmap(":/icon/icon/frameoff.png");
        QPixmap scaledPixmapFrameOff = frameoffPixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        customWidget->frameLabel->setPixmap(scaledPixmapFrameOff);
        customWidget->frameLabelText->setText("未检测到火焰");
    }
}

void Widget::updateLightLCD(int data)
{
    customWidget->lightLCD->display(data);
}

/***根据标志位判断当前的按钮处于什么状态，点击时根据当前状态去给继电器传递1/0***/
void Widget::relayButtonClicked()
{

    QPixmap relayLabelOnPixmap(":/icon/icon/relayon.png");
    QPixmap relayLabelPixmap(":/icon/icon/relay.png");

    QPixmap newrelayOn = relayLabelOnPixmap.scaled(150,150);
    QPixmap newrelay = relayLabelPixmap.scaled(150,150);

    if(!customWidget->relayButtonState)
    {
            customWidget->relay->changeRelayState(1);
            customWidget->relayLabel->setPixmap(newrelayOn);
            customWidget->relayButton->setText("关闭");
            customWidget->relayButtonState = true;
    }else{
            customWidget->relay->changeRelayState(0);
            customWidget->relayLabel->setPixmap(newrelay);
            customWidget->relayButton->setText("打开");
            customWidget->relayButtonState = false;
    }
}

/***根据传递过来的光电状态去改变当前Label的样式***/
void Widget::handleLightElectricState(int state)
{
   // qDebug()<<"LightElectric state"<<state;
    QPixmap lightLabelPixmap;

    if(state == 0){
        lightLabelPixmap.load(":/icon/icon/norlightswitch.png");
        customWidget->lightLabelText->setText("未检测遮挡");
    }else {
        lightLabelPixmap.load(":/icon/icon/lightswitch.png");
        customWidget->lightLabelText->setText("检测遮挡");
    }

    QPixmap scaledLightLabelPixmap = lightLabelPixmap.scaled(200, 200, Qt::KeepAspectRatio);

    customWidget->lightLabel->setPixmap(scaledLightLabelPixmap);
}


