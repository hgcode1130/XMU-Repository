#include "sms.h"

sms::sms(QWidget *parent) : QWidget(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    customWidget = new SmsCustomWidget();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    scene->setSceneRect(0, 0, screenWidth, screenHeight);
    view->setFixedSize(screenWidth, screenHeight);
    customWidget->resize(screenWidth, screenHeight);
    customWidget->showFullScreen();

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    proxyWidget = scene->addWidget(customWidget);
    proxyWidget->setTransformOriginPoint(proxyWidget->boundingRect().center());
    proxyWidget->setZValue(100);

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
    //连接按钮的信号和槽函数
    connect(customWidget->backButton, &QPushButton::clicked, this, &sms::backButtonClicked);
    connect(customWidget->lineEdit_sendsms,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_sendsms(QString)));
    connect(customWidget->syszuxpinyin_sendsms,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_sendsms(QString)));
    connect(customWidget->sendsmsButton, &QPushButton::clicked, this, &sms::sendsmsButtonClicked);
    // 设置 QGraphicsView 为中心控件或根据需要进行布局
//    setCentralWidget(view);
}

void sms::sendsmsButtonClicked()
{
    QString contact = customWidget->titleLabel->text();
    QString message = customWidget->lineEdit_sendsms->text();
    emit sendsms(contact,message);
}

void sms::backButtonClicked()
{
    this->hide();
}

void sms::myslotgetphone(QString phonenum,QString msgshow)
{
    if(phonenum == customWidget->titleLabel->text() || customWidget->titleLabel->text()=="")
    {
        qDebug()<<"msgshow"<<msgshow;

        customWidget->titleLabel->setText(phonenum);
        if(msgshow.contains("recv:",Qt::CaseInsensitive)){
            msgshow.remove("recv:",Qt::CaseInsensitive);
            QWidget *recvWidget = new QWidget(this);
            QHBoxLayout *hlayout = new QHBoxLayout();
            recvWidget->setLayout(hlayout);

            ChatBubbleItem * recvItem = new ChatBubbleItem(msgshow,ChatBubbleItem::Received,customWidget->list->parentWidget());
            QSpacerItem *springItem = new QSpacerItem(0, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
            QListWidgetItem *item = new QListWidgetItem(customWidget->list);
            //recvItem->setFixedWidth(this->width());
            QSize size = recvItem->fontRect(msgshow);

            springItem->changeSize((customWidget->list->width()-size.width() - 50),1);
            // 将弹簧项添加到布局中
            hlayout->addWidget(recvItem,Qt::AlignLeft);
            hlayout->addItem(springItem);

            item->setSizeHint(size);
            //item->setSizeHint(QSize(50,100));
            customWidget->list->addItem(item);
            customWidget->list->setItemWidget(item,recvWidget);
        }else if(msgshow.contains("send:",Qt::CaseInsensitive)){
            QWidget *sendWidget = new QWidget(this);
            QHBoxLayout *hlayout = new QHBoxLayout();
            sendWidget->setLayout(hlayout);
            msgshow.remove("send:", Qt::CaseInsensitive);

            ChatBubbleItem *sendItem = new ChatBubbleItem(msgshow, ChatBubbleItem::Sent, customWidget->list);
            // 创建一个弹簧项，并设置其最小和最大尺寸
            QSpacerItem *springItem = new QSpacerItem(0, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
            QListWidgetItem *item = new QListWidgetItem(customWidget->list);
            QSize size = sendItem->fontRect(msgshow); // 获取 sendItem 的推荐大小

            sendWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 设置为Expanding以允许部件扩展
            springItem->changeSize((customWidget->list->width()-size.width() - 50),1);
            // 将弹簧项添加到布局中
            hlayout->addItem(springItem);
            hlayout->addWidget(sendItem, Qt::AlignRight);
            item->setSizeHint(size); // 设置列表项的大小提示
            customWidget->list->addItem(item);
            customWidget->list->setItemWidget(item, sendWidget);
    }
    }

}

void sms::keyboardshow_sendsms(QString data)
{
    customWidget->syszuxpinyin_sendsms->lineEdit_window->setText(data);
    customWidget->syszuxpinyin_sendsms->resize(1050,480);
    customWidget->syszuxpinyin_sendsms->move(120,240);
    customWidget->syszuxpinyin_sendsms->show();
}

void sms::confirmString_sendsms(QString gemfield)
{
    customWidget->lineEdit_sendsms->setText(gemfield);
}
