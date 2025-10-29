#include "mymap.h"
#include "ui_mymap.h"
#include "scribblearea.h"

MyMap::MyMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMap)
{
    ui->setupUi(this);
    ScribbleArea *S = new ScribbleArea();
}

MyMap::~MyMap()
{
    delete ui;
}
