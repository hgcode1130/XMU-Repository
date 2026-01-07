#include "signalslots.h"
#include "ui_signalslots.h"

SIgnalSlots::SIgnalSlots(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SIgnalSlots)
{
    ui->setupUi(this);
    //按钮1和LcdNumber1建立信号槽连接
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(pushbutten_1_Slot()));
    //按钮2和LcdNumber2建立信号槽连接
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(pushbutten_2_Slot()));
    //按钮3和LcdNumber1.2.3建立信号槽连接
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(pushbutten_1_Slot()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(pushbutten_2_Slot()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(pushbutten_3_Slot()));
}

SIgnalSlots::~SIgnalSlots()
{
    delete ui;
}
void SIgnalSlots::pushbutten_1_Slot()
{
    //在lcdNumber_1中数字加1
    ui->lcdNumber_1->display(ui->lcdNumber_1->value() + 1);
}
void SIgnalSlots::pushbutten_2_Slot()
{
    //在lcdNumber_2中数字加1
    ui->lcdNumber_2->display(ui->lcdNumber_2->value() + 1);
}
void SIgnalSlots::pushbutten_3_Slot()
{
    //在lcdNumber_3中数字加1
    ui->lcdNumber_3->display(ui->lcdNumber_3->value() + 1);

}


