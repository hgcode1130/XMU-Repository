#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QList>
#include <QDebug>
#include <QTextCodec>
#include <QString>
#include <QTimer>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QtNetwork/QNetworkAddressEntry>
#include <QtNetwork/QNetworkInterface>
#include <QListWidgetItem>
#include <QByteArray>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    connect(customWidget->ui->pushButton_back,&QPushButton::clicked,this,&MainWindow::on_pushButton_back_clicked);
    connect(customWidget->ui->pushButton_sendmessage,&QPushButton::clicked,this,&MainWindow::on_pushButton_sendmessage_clicked);
    connect(customWidget->ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);

    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);

    mynewsms = new newsms();
    connect(mynewsms,SIGNAL(sendnewsms(QString,QString)),this,SLOT(myslotsendnewmsg(QString,QString)));
    int ret = serial_select();
    if(ret < 0){
        QMessageBox::warning(this,tr("警告"),tr("模组丢失，请插入模组"));
        return;
    }

    serialPort.write("AT+CPIN?\r");
    serialPort.flush();
    recvmessage();

    serialPort.clear();
    serialPort.write("AT+CNMI=1,2,0,1,0\r");
    serialPort.flush();
    qDebug()<<"CNMI";
    sleep(1);
    recvmessage();

    serialPort.write("AT+CMGF=1\r");
    serialPort.flush();
    sleep(1);
    recvmessage();

    serialPort.write("AT+CSMP=17,167,0,8\r");
    serialPort.flush();
    sleep(1);
    recvmessage();

    serialPort.write("AT+CSCS=\"UCS2\"\r");
    serialPort.flush();
    sleep(1);
    recvmessage();

    Operator = true;
    serialPort.write("AT+COPS?\r");
    serialPort.flush();
    sleep(1);
    recvmessage();

    QTimer *mytimer = new QTimer(this);
    connect(mytimer,SIGNAL(timeout()),this,SLOT(myslot()));
    mytimer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendmessage()
{
    sleep(1);
    if (serialPort.waitForReadyRead(1000))
    {
        QByteArray responseData = serialPort.readAll();
        QString response(responseData);
        qDebug() << "Response: " << response;
    }
    else
    {
        qDebug() << "Timeout while waiting for response.";
    }
}

void MainWindow::recvmessage()
{
    serialPort.flush();
    QByteArray responseData = serialPort.readAll();
    QString response(responseData);
    qDebug() << "Response: " << response <<Operator;
    if(response.contains("CHN-CT", Qt::CaseSensitive))
    {
        Operator = false;
    }
    if(response.contains("+CME ERROR: 10",Qt::CaseInsensitive)){
        QMessageBox::warning(this,tr("警告"),tr("未找到SIM卡，请检查插卡是否稳定"));
        return;
     }
    if(response.contains("CMT", Qt::CaseSensitive))
    {
        //QRegularExpression phoneNumberRegex(R"(\002B00380036(\d+))");
        QString phoneNumber_ucs2;
        QString phoneNumber;

        QRegularExpression regex("\\d");
        // 在字符串中查找匹配的第一个数字
        QRegularExpressionMatch match = regex.match(response);

        // 检查是否有匹配
        if (match.hasMatch())
        {
            //dianxin
            QString matchedNumber = match.captured();
            qDebug() << matchedNumber;
            if(matchedNumber == "1")
            {
                int startIdex_dianxin = response.indexOf("1");
                phoneNumber = response.mid(startIdex_dianxin,11);
                qDebug() << "Phone Number dianxin:"  <<phoneNumber;
            }
            else
            {
                //yidong or liantong
                //int startIdex = response.indexOf("002B00380036") + QString("002B00380036").length();
                int startIdex = response.indexOf("0031");
                phoneNumber_ucs2 = response.mid(startIdex,44);

                qDebug() << "Phone Number:" << phoneNumber_ucs2;
                for (int i = 0; i < phoneNumber_ucs2.length(); i += 4)
                {
                    QString hex = phoneNumber_ucs2.mid(i, 4);
                    bool ok;
                    uint value = hex.toUInt(&ok, 16);
                    if(ok)
                    {
                        if (value >= '0' && value <= '9')
                        {
                            phoneNumber.append(QChar(value));
                        }
                    }
                }
            }
        }

        qDebug() << "Phone Number:" << phoneNumber_ucs2 <<phoneNumber;
        int lastIndex = response.lastIndexOf("\r\n");
        int secondLastIndex = response.lastIndexOf("\r\n", lastIndex - 1);
        QString extractedData = response.mid(secondLastIndex + 2, lastIndex - secondLastIndex - 2);
        QString result;
        for (int i = 0; i < extractedData.length(); i += 4)
        {
            QString hex = extractedData.mid(i, 4);
            bool ok;
            uint value = hex.toUInt(&ok, 16);

            if (ok)
            {
                if (value >= '0' && value <= '9')
                {
                    result.append(QChar(value));
                }
                else if ((value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z'))
                {
                    result.append(QChar(value));
                }
                else
                {
                    QByteArray byteArray = QByteArray::fromHex(hex.toUtf8());
                    QString decodedText;
                    if(byteArray.size() == 1){
                        uchar lastByte = static_cast<uchar>(byteArray.at(byteArray.size() - 1));
                        decodedText.append(QChar(lastByte));
                    }else{
                    for (int i = 0; i < byteArray.size(); i += 2)
                    {
                        uchar byte1 = static_cast<uchar>(byteArray.at(i));
                        uchar byte2 = static_cast<uchar>(byteArray.at(i + 1));
                        ushort unicodeValue = (byte1 << 8) | byte2;
                        decodedText.append(QChar(unicodeValue));
                    }
                    }
                    result.append(decodedText);
                }
            }
        }
        auto it = myMap.find(phoneNumber);
        if (it == myMap.end())
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/user.png"), phoneNumber+"\n"+result);
            item->setData(Qt::UserRole, phoneNumber);
            // 调整图标大小
            customWidget->ui->listWidget->setIconSize(QSize(60, 60));
            customWidget->ui->listWidget->addItem(item);
            sms* mysms = new sms();
            connect(this,SIGNAL(mysignalphone(QString,QString)),mysms,SLOT(myslotgetphone(QString,QString)));
            connect(mysms,SIGNAL(sendsms(QString,QString)),this,SLOT(myslotsendnewmsg(QString,QString)));
            myMap.insert(phoneNumber,mysms);
            emit mysignalphone(phoneNumber,"recv: "+result + "\n");
        }
        else
        {
            int count = customWidget->ui->listWidget->count();
            for (int i = 0; i < count; ++i)
            {
                QListWidgetItem *item = customWidget->ui->listWidget->item(i);
                QString itemText = item->text();

                // 检查文本是否以目标前缀开头
                if (itemText.startsWith(phoneNumber))
                {
                    // 修改文本或执行其他操作
                    QString newText = phoneNumber+"\n"+result;
                    item->setText(newText);
                }
            }
            emit mysignalphone(phoneNumber,"recv: "+result + "\n");
        }
    }
}

int MainWindow::serial_select()
{

//    ui->recvmessage->setReadOnly(true);
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::const_iterator it;
    QString serialportname;

    serialPort.setPortName("/dev/ttyUSB2");
    serialPort.setBaudRate(QSerialPort::Baud115200);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort.open(QIODevice::ReadWrite))
    {
        return -1;
    }
    return 0;

}

void MainWindow::myslot()
{
    recvmessage();
}

void MainWindow::myslotsendnewmsg(QString contact, QString message)
{

    qDebug() << contact <<message;
    QString qstr_phonenum = contact;
    //qDebug() << qstr_phonenum <<qstr_phonenum.toUcs4();
    QString ucs2HexString;
    QVector<uint> ucs4Data = qstr_phonenum.toUcs4();
    for (const uint ch : ucs4Data)
    {
        //qDebug() << ch;
        QString hexString = QString::number(ch, 16);
        ucs2HexString.append("00"+hexString);
    }
    //qDebug() << ucs2HexString;

    ucs2HexString = "AT+CMGS=\"" + ucs2HexString + "\"\r";
    //qDebug() << ucs2HexString;

    QByteArray byteArray = ucs2HexString.toUtf8();
    serialPort.write(byteArray);
    serialPort.flush();
    sendmessage();
    QString qstr_message = message;
    QByteArray ucs2Data;
    QByteArray utf82Data = message.toUtf8() ;
    for (int i = 0; i < qstr_message.length(); ++i)
    {
        ushort ch = qstr_message[i].unicode();
        ucs2Data.append((ch >> 8) & 0xFF);
        ucs2Data.append(ch & 0xFF);
    }
	serialPort.write(ucs2Data.toHex());
    serialPort.flush();
    sendmessage();
    //qDebug() << ucs2Data.toHex() <<ucs2Data.length();
    //if(Operator == true)
    //{
    //    serialPort.write(ucs2Data.toHex());
    //    serialPort.flush();
    //    sendmessage();
    //}
    //else if(Operator == false)
    //{
    //   serialPort.write(utf82Data);
    //    serialPort.flush();
    //    sendmessage();
    //}
    serialPort.write("\x1A");
    serialPort.flush();
    sendmessage();


    auto it = myMap.find(contact);
    if (it == myMap.end())
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/user.png"), contact+"\n"+message);
        item->setFont(QFont("Noto Sans CJK SC Regular",18));
        item->setData(Qt::UserRole, contact);
        // 调整图标大小
         customWidget->ui->listWidget->setFont(QFont("Noto Sans CJK SC Regular",18));
        customWidget->ui->listWidget->setIconSize(QSize(70, 70));
        customWidget->ui->listWidget->addItem(item);
        sms* mysms = new sms();
        connect(this,SIGNAL(mysignalphone(QString,QString)),mysms,SLOT(myslotgetphone(QString,QString)));
        connect(mysms,SIGNAL(sendsms(QString,QString)),this,SLOT(myslotsendnewmsg(QString,QString)));
        myMap.insert(contact,mysms);
        emit mysignalphone(contact,"send: "+message + "\n");
        mysms->showFullScreen();
    }
    else
    {
        int count = customWidget->ui->listWidget->count();
        for (int i = 0; i < count; ++i)
        {
            QListWidgetItem *item = customWidget->ui->listWidget->item(i);
            QString itemText = item->text();

            // 检查文本是否以目标前缀开头
            if (itemText.startsWith(contact))
            {
                // 修改文本或执行其他操作
                QString newText = contact+"\n"+message;
                item->setText(newText);
            }
        }
        emit mysignalphone(contact,"send: "+message + "\n");
        it.value()->showFullScreen();
    }
}

void MainWindow::on_pushButton_sendmessage_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    mynewsms->setFixedSize(screenWidth,screenHeight);
    mynewsms->showFullScreen();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString qstrphone = item->data(Qt::UserRole).toString();
    auto it = myMap.find(qstrphone);
    if (it != myMap.end())
    {
        // 找到了，可以调用 show 函数
        it.value()->showFullScreen();
    }
}

void MainWindow::on_pushButton_back_clicked()
{
    this->close();
    QApplication::quit();
}
