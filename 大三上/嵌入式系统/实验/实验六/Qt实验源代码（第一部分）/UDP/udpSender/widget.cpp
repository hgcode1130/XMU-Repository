#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(btnClock()));
    sender = new QUdpSocket(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::btnClock()
{
    QByteArray datagram = ui->textEdit->toPlainText().toLatin1();
       sender->writeDatagram(datagram.data(),datagram.size(),
                             QHostAddress::Broadcast,45454);
}

