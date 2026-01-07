#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //设置窗口状态
    setWindowState(Qt::WindowActive);
    //设置窗口
    setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(btnOpenSlot()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(btnSaveSlot()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(btnCopySlot()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showFileInfo(QString pth)
{
    //创建文件信息类
    QFileInfo info(pth);
    if(info.isReadable())
        ui->textBrowser_3->append("是否可读: 是");
    else
        ui->textBrowser_3->append("是否可读: 否");
    if(info.isWritable())
        ui->textBrowser_3->append("是否可写: 是");
    else
        ui->textBrowser_3->append("是否可写: 否");
    //上次修改时间
   QString lastchangeTime = "上次修改时间：" + info.lastModified().toString("yyyy-MM-dd hh:mm:ss");
   //上次读取时间
   QString lastreadTime = "上次读取时间：" + info.lastRead().toString("yyyy-MM-dd hh:mm:ss");
   ui->textBrowser_3->append(lastchangeTime);
   ui->textBrowser_3->append(lastreadTime);
   //计算文件大小
   float size = (float)info.size()/1024/1024;
   QString sizeinfo = "文件大小：" + QString::number(size) + "MB";
   ui->textBrowser_3->append(sizeinfo);
}

void Dialog::btnOpenSlot()
{
    ui->textBrowser_3->clear();
    ui->textBrowser->clear();
    //获取文件路径
    QString pth = QFileDialog::getOpenFileName(this,"打开","/home/linux","ALL(*.*)");
    ui->textBrowser->setText(pth);
    qDebug() << pth;
    showFileInfo(pth);
}

void Dialog::btnSaveSlot()
{
    ui->textBrowser_2->clear();
    QString pth =QFileDialog::getSaveFileName(this,"保存","/home/linux","ALL(*.*)");
    ui->textBrowser_2->setText(pth);
    qDebug() << pth;
}

void Dialog::btnCopySlot()
{
      mtd = new MyThread(ui->textBrowser->toPlainText(),ui->textBrowser_2->toPlainText());
      mtd->start();
      connect(mtd,SIGNAL(messageBoxSignal()),this,SLOT(messageBoxSlot()));
      connect(mtd,SIGNAL(btnUnAble()),this,SLOT(btnUnAbleSlot()));
      connect(mtd,SIGNAL(progressBarSignal(int)),this,SLOT(setProgressBarSlot(int)));
      connect(mtd,SIGNAL(messageBoxInfoSignal()),this,SLOT(messageBoxInfoSlot()));
      connect(mtd,SIGNAL(btnAble()),this,SLOT(btnAbleSlot()));
}
//提示窗口
void Dialog::messageBoxSlot()
{
    QMessageBox::warning(this,"提示","请选择路径");
}
//关闭按钮
void Dialog::btnUnAbleSlot()
{
    ui->pushButton_3->setEnabled(false);
}
//改变进度条
void Dialog::setProgressBarSlot(int value)
{
    ui->progressBar->setValue(value);
}

void Dialog::messageBoxInfoSlot()
{
    QMessageBox::information(this,"提示","文件拷贝成功");
}

void Dialog::btnAbleSlot()
{
   ui->pushButton_3->setEnabled(true);
}


