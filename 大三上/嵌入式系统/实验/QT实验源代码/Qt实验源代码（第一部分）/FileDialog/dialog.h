#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QMessageBox>
#include <QtMath>
#include "mythread.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    MyThread *mtd;
    void showFileInfo(QString);
private slots:
    void btnOpenSlot();
    void btnSaveSlot();
    void btnCopySlot();
    void messageBoxSlot();              //弹窗
    void btnUnAbleSlot();               //设置按钮不可用
    void setProgressBarSlot(int value); //改变进度条
    void messageBoxInfoSlot();
    void btnAbleSlot();
};

#endif // DIALOG_H
