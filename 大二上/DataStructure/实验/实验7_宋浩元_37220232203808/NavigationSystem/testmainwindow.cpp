#include "testmainwindow.h"
#include "ui_testmainwindow.h"

TestMainWindow::TestMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestMainWindow)
{
    ui->setupUi(this);
}

TestMainWindow::~TestMainWindow()
{
    delete ui;
}
