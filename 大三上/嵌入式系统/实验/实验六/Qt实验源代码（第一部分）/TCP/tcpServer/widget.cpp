#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::LocalHost,6666))
    {  //本地主机的6666端口，如果出错就输出错误信息，并关闭
        qDebug() << "error" <<tcpServer->errorString();
        close();
    }
    //连接信号和相应槽函数
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMessage()
{
    //用于暂存我们要发送的数据
    QByteArray block;
    //使用数据流写入数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_4_6);
    out<<(quint16) 0;
    qDebug()<<ui->textEdit_send->toPlainText();
    out<<ui->textEdit_send->toPlainText();
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));

    //我们获取已经建立的连接的子套接字
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection,SIGNAL(disconnected()),clientConnection,
           SLOT(deleteLater()));
    clientConnection->write(block);
    clientConnection->disconnectFromHost();

    //发送数据成功后，显示提示
    ui->statusLabel->setText("send message successful!!!");
    qDebug() <<"send message successful!!!";
}
