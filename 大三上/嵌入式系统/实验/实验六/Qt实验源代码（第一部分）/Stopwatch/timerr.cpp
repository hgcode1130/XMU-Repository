#include "timerr.h"
#include "ui_timerr.h"

Timerr::Timerr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timerr)
{
    ui->setupUi(this);
}

Timerr::~Timerr()
{
    delete ui;
}
void Timerr::start()
{
    timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->start(10);
    //超时发出信号
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdateSlot()));
    timeUpdateSlot();
    ui->lcdNumber->show();
}
void Timerr::stop()
{
    timer->stop();
}
//超时处理槽函数
void Timerr::timeUpdateSlot()
{
    time =  QString::number(s).append(":").append(QString::number(ms))
            .append(QString::number(timerBegin++));
    if(timerBegin == 10)
    {
       ms++;
      timerBegin=0;
    }
    if(ms ==10)
    {
        s++;
        ms =0;
        timerBegin=0;
    }
    if(s==60)
    {
        s=0;
        timerBegin =0;
    }
    ui->lcdNumber->display(time);
}
