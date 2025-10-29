#include "welcom.h"
#include "ui_welcom.h"
#include "sigin.h"
#include "login.h"
#include "main.h"
#include "mymap.h"
Welcom::Welcom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Welcom)
{
    //loading!!!
    ui->setupUi(this);

    this->setWindowTitle("地图");

    QImage *img = new QImage(":/src/img/logo.jpg");
    originalPixmap = QPixmap::fromImage(*img);
    ui->logo->setPixmap(originalPixmap.scaled(ui->logo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 设置 QLabel 的文字
    ui->Title->setText("厦门大学翔安校区导航系统");

    // 设置 QLabel 的对齐方式
    ui->Title->setAlignment(Qt::AlignCenter);

    // 设置 QLabel 的字体样式
    QFont font("Arial", 24, QFont::Bold);
    ui->Title->setFont(font);

    // 设置 QLabel 的样式表（可选）
    ui->Title->setStyleSheet("QLabel { color: white; font-size: 36px; font-weight: bold; }");

    this->setWindowIcon(QIcon(":/src/icon/src/img/logo_mini.jpg"));
    setAttribute(Qt::WA_DeleteOnClose);
}

Welcom::~Welcom()
{
    delete ui;
}

void Welcom::on_sigin_buttom_clicked()
{
    start->open_sigin();
}

void Welcom::on_login_button_clicked()
{
   start->open_login();
}

void Welcom::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // // 窗口大小改变时调整图片大小
    // if (!originalPixmap.isNull()) {
    //     ui->logo->setPixmap(originalPixmap.scaled(ui->logo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // }
    // // 动态设置背景图片
    // QString backgroundStyle = QString("QWidget {"
    //                                   "background-image: url(:/src/img/background.jpg);"
    //                                   "background-position: center;"
    //                                   "background-repeat: no-repeat;"
    //                                   "background-size: cover;"
    //                                   "}");
    // this->setStyleSheet(backgroundStyle);
}
