#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(startSlot()));
    connect(ui->pushButton_stop,SIGNAL(clicked()),this,SLOT(stopSlot()));
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::startSlot()
{
    timer = new Timerr(this);
    timer->show();
    timer->start();
}
void Dialog::stopSlot()
{
      timer->stop();
}
