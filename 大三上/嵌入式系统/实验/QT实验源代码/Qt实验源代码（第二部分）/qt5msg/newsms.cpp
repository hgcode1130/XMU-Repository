#include "newsms.h"

newsms::newsms(QWidget *parent) : QWidget(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    customWidget = new NewSmsCustomWidget();
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
    connect(customWidget->newsmsbackButton, &QPushButton::clicked, this, &newsms::newsmsbackButtonClicked);
    connect(customWidget->sendButton, &QPushButton::clicked, this, &newsms::sendButtonClicked);
    connect(customWidget->lineEdit_sendphonenumber,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_sendphonenumber(QString)));
    connect(customWidget->syszuxpinyin_sendphonenumber,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_sendphonenumber(QString)));
    connect(customWidget->textEdit_sendmessage,SIGNAL(send_show(QString)),this,SLOT(keyboardshow_sendmessage(QString)));
    connect(customWidget->syszuxpinyin_sendmessage,SIGNAL(sendPinyin(QString)),this,SLOT(confirmString_sendmessage(QString)));
    // 设置 QGraphicsView 为中心控件或根据需要进行布局
//    setCentralWidget(view);

}

void newsms::newsmsbackButtonClicked()
{
    this->hide();
}

void newsms::sendButtonClicked()
{
    QRegularExpression regex("^[0-9]{11}$");
    if (!regex.match(customWidget->lineEdit_sendphonenumber->text()).hasMatch())
    {
        QMessageBox::warning(this,tr("Warning"),tr("请输入正确格式的手机号"));
    }
    else
    {
        QString contact = customWidget->lineEdit_sendphonenumber->text();
        QString message = customWidget->textEdit_sendmessage->text();
        qDebug()<<"contact"<<contact<<"message"<<message;
        this->hide();
        emit sendnewsms(contact,message);
        // 清空输入框
        customWidget->lineEdit_sendphonenumber->clear();
        customWidget->textEdit_sendmessage->clear();
    }
}


void newsms::keyboardshow_sendphonenumber(QString data)
{
    customWidget->syszuxpinyin_sendphonenumber->lineEdit_window->setText(data);
    customWidget->syszuxpinyin_sendphonenumber->resize(1050,480);
    customWidget->syszuxpinyin_sendphonenumber->move(120,240);
    customWidget->syszuxpinyin_sendphonenumber->show();

}

void newsms::confirmString_sendphonenumber(QString gemfield)
{
     customWidget->lineEdit_sendphonenumber->setText(gemfield);
}

void newsms::keyboardshow_sendmessage(QString data)
{
    customWidget->syszuxpinyin_sendmessage->lineEdit_window->setText(data);
    customWidget->syszuxpinyin_sendmessage->resize(1050,480);
    customWidget->syszuxpinyin_sendmessage->move(120,240);
    customWidget->syszuxpinyin_sendmessage->show();
}

void newsms::confirmString_sendmessage(QString gemfield)
{
    customWidget->textEdit_sendmessage->setText(gemfield);
}
