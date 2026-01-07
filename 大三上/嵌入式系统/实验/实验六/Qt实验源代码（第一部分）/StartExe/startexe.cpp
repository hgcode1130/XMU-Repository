#include "startexe.h"
#include "ui_startexe.h"

StartExe::StartExe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartExe)
{
    ui->setupUi(this);
}

StartExe::~StartExe()
{
    delete ui;
}

void StartExe::on_pushButton_clicked()
{
    QProcess::execute("/home/linux/Qt/StartExe/app",QStringList());//以阻塞方式打开外部程序
}

void StartExe::on_pushButton_2_clicked()
{
    QProcess process(this);
    process.start("/home/linux/Qt/StartExe/app");//以子进程的方式打开外部程序
    process.waitForFinished();//不可少，不然外部程序无法打开
}

void StartExe::on_pushButton_3_clicked()
{
    QProcess::startDetached("/home/linux/Qt/StartExe/app",QStringList());//以分离方式打开外部程序
}
