#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sigin.h"
#include "login.h"
#include "welcom.h"
#include "scribblearea.h"
#include "mymap.h"
#include <mysql.h>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = new ScribbleArea();
    ui->scrollArea->setWidget(s);
    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearAllData() {
    // 清空数据库中的点和连接
    MySQL& sql = MySQL::getInstance();
    sql.clearAllPoints();

    // 清空地图上的显示
    s->clearImage();
    s->update();

    // 提示用户操作成功
    QMessageBox::information(this, "提示", "所有点和连接已成功清空！");
}



