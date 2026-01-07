#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScreen>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include "lis3dhdevice.h"
#include "painter.h"
#include "circularprocess.h"
#include "servodevice.h"
#include "dcdevice.h"
#include "stepperdevice.h"

class CustomWidget;
class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();

public slots:
    //当前页发生变化
    void handleIndexChange(int index);

    //转动舵机
    void trunServo(int percent);

    //反转直流电机
    void backSlot();

    //停止直流电机
    void stopFanSlot();

    //正转直流电机
    void fanButtonSlot();

    //退出按钮
    void exitSlot();

private:

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;

signals:
    void Set0();
    void Set1();
    void Set2();
};

class CustomWidget : public QTabWidget {
  Q_OBJECT
public:
    CustomWidget(QWidget *parent = nullptr) : QTabWidget(parent) {
        QFont tabBarfont("Noto Sans CJK SC Regular");// 设置标签字体
        this->setFont(tabBarfont);
        this->setFocusPolicy(Qt::NoFocus);// 设置焦点策略，无焦点
        this->setStyleSheet(
            "QTabBar::tab, QTabBar::tab:selected, QTabBar::tab:hover {"
            "  font: 12pt 'Noto Sans CJK SC Regular';"
            "  outline: none;"
            "  border: none;"
            "  border-top-left-radius: 8px;"
            "  border-top-right-radius: 8px;"
            "  width: 125px;"
            "  height: 50px;"
            "  color: rgb(102, 102, 102);"
            "  background-color: transparent;"
            "}"
            "QTabBar::tab:first {"
            "  margin-left: 2px;"
            "  outline: none;"
            "}"
            "QTabBar::tab:selected {"
            "  font-weight: bold;"
            "  background: #5e98ea;"
            "  color: white;"
            "  outline: none;"
            "}"
            "QTabBar::tab:hover {"
            "  outline: none;"
            "}"
        );

        //添加页数
        Page1 = new QWidget(this);// 舵机控制页面
        QGridLayout *Page1Layout = new QGridLayout(Page1);// 使用网格布局

        Page2 = new QWidget(this);// 直流电机控制页面
        QGridLayout *Page2Layout = new QGridLayout(Page2);

        Page3 = new QWidget(this);// 步进电机控制页面
        QGridLayout *Page3Layout = new QGridLayout(Page3);

        topexit = new QPushButton(this);// 创建退出按钮
        topexit->setStyleSheet("QPushButton { border: none;outline: none;}"); // 设置按钮样式
        topexit->setIcon(QIcon(":/icon/icon/exit.png"));// 设置按钮图标
        topexit->setIconSize(QSize(40, 40)); // 设置图标大小

        QFont topexitfont("Noto Sans CJK SC Regular");
        topexit->setFont(topexitfont);// 设置按钮字体

        this->addTab(Page1, "舵机");// 添加舵机控制标签
        this->addTab(Page2,"直流电机");// 添加直流电机控制标签
        this->addTab(Page3, "步进电机");// 添加步进电机控制标签
        this->setCornerWidget(topexit);// 将退出按钮设置在角落
        // 设置默认显示的选项卡
        this->setCurrentIndex(0);

        //舵机

        servo = new servoDevice();
        servo->initServo();// 舵机设备初始化

        QLabel *showServoDIP = new QLabel();
        QPixmap servoPixmap(":/icon/icon/Servo.png");

        double scaleFactor = 1;

        int newWidth = static_cast<int>(servoPixmap.width() * scaleFactor);
        int newHeight = static_cast<int>(servoPixmap.height() * scaleFactor);

        QPixmap scaledPixmap = servoPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);

        showServoDIP->setPixmap(scaledPixmap);

        int screenWidth = QApplication::primaryScreen()->geometry().width();
        int screenHeight = QApplication::primaryScreen()->geometry().height();

        // 计算宽度和高度
        int width = static_cast<int>(screenWidth * 0.449);
        int height = static_cast<int>(screenHeight * 0.76);

        // 创建部件
        round1 = new CircularProcess(this);
        round1->setRange(0, 180);
        round1->setFixedSize(width,height);
        round1->setStyleSheet("border: none;background-color: transparent;");

        QLabel *spaceLabel = new QLabel();
        spaceLabel->setFixedHeight(70);

        Page1Layout->addWidget(spaceLabel,0,0,Qt::AlignCenter|Qt::AlignBottom);
        Page1Layout->addWidget(round1,1,0,Qt::AlignCenter|Qt::AlignBottom);
        Page1Layout->addWidget(showServoDIP,2,0,Qt::AlignCenter|Qt::AlignTop);

        //直流电机
        dc = new dcDevice();
        QLabel *showDcDIP = new QLabel();
        QPixmap dcPixmap(":/icon/icon/Dc.png");

        double dcScaleFactor = 1;

        int dcNewWidth = static_cast<int>(dcPixmap.width() * dcScaleFactor);
        int dcNewHeight = static_cast<int>(dcPixmap.height() * dcScaleFactor);

        QPixmap dcScaledPixmap = dcPixmap.scaled(dcNewWidth, dcNewHeight, Qt::KeepAspectRatio);
        showDcDIP->setPixmap(dcScaledPixmap);

        fan = new Painter();
        fan->setFixedSize(500, 500);

        QLabel *showDcDIPbackground = new QLabel();
        QPixmap backgroundPixmap(":/icon/icon/background.png");
        showDcDIPbackground->setPixmap(backgroundPixmap);
        showDcDIPbackground->setFixedSize(800, 70);
        showDcDIPbackground->setObjectName("btnLabel");
        showDcDIPbackground->setStyleSheet("#btnLabel { border-radius: 10px; background-color:transparent}");

        fanBackButton = new QPushButton();
        fanBackButton->setFixedSize(50,50);
        fanBackButton->setStyleSheet(
                    "QPushButton {"
                    "border: none; "
                    "outline: none; "
                    "image: url(:/icon/icon/right.png);"
                    "width: 50px; "
                    "height: 50px; "
                    "}"
                    "QPushButton:pressed {"
                    "image: url(:/icon/icon/rightclicked.png);"
                    "width: 50px; "
                    "height: 50px; "
                    "}"
                );

        fanStopButton = new QPushButton();
        fanStopButton->setFixedSize(50,50);
        fanStopButton->setStyleSheet(
                    "QPushButton {"
                    "border: none; "
                    "outline: none; "
                    "image: url(:/icon/icon/stop.png);"
                    "width: 50px; "
                    "height: 50px; "
                    "}"
                    "QPushButton:pressed {"
                    "image: url(:/icon/icon/stopclicked.png);"
                    "width: 50px; "
                    "height: 50px; "
                    "}"
                );

        fanButton = new QPushButton();
        fanButton->setFixedSize(50,50);
        fanButton->setStyleSheet(
                    "QPushButton {"
                    "border: none; "
                    "outline: none; "
                    "image: url(:/icon/icon/left.png);"
                    "width: 50px; "
                    "height: 50px; "
                    "}"
                    "QPushButton:pressed {"
                    "image: url(:/icon/icon/leftclicked.png);"
                    "width: 50px; "
                    "height: 50px; "
                    "}"
                );

        timer = new QTimer(this);
        timer->start(10);

        QLabel *dcSpaceLabel = new QLabel();
        dcSpaceLabel->setFixedHeight(70);

        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(fan, 0, Qt::AlignHCenter);

        QHBoxLayout *horizontalLayout = new QHBoxLayout(showDcDIPbackground);
        horizontalLayout->addWidget(fanButton, Qt::AlignCenter);
        horizontalLayout->addWidget(fanStopButton, Qt::AlignCenter);
        horizontalLayout->addWidget(fanBackButton, Qt::AlignCenter);

        verticalLayout->addWidget(fan, 0, Qt::AlignHCenter);
        verticalLayout->addWidget(showDcDIPbackground, 0, Qt::AlignHCenter);
        verticalLayout->addWidget(showDcDIP, 0, Qt::AlignHCenter);
        verticalLayout->setContentsMargins(0,10,0,10);

        Page2Layout->addLayout(verticalLayout, 1, 0, 1, 3, Qt::AlignCenter);

        //步进电机
        stepper = new stepperDevice();

        thread = new QThread();
        stepper->moveToThread(thread);

        QLabel *showStepperDIP = new QLabel();
        QPixmap stepperPixmap(":/icon/icon/Stepper.png");

        double stepperScaleFactor = 1;

        int stepperNewWidth = static_cast<int>(stepperPixmap.width() * stepperScaleFactor);
        int stepperNewHeight = static_cast<int>(stepperPixmap.height() * stepperScaleFactor);

        QPixmap stepperScaledPixmap = stepperPixmap.scaled(stepperNewWidth, stepperNewHeight, Qt::KeepAspectRatio);

        showStepperDIP->setPixmap(stepperScaledPixmap);

        part1 = new QPushButton();
        part2 = new QPushButton();
        part3 = new QPushButton();
        part4 = new QPushButton();
        part0 = new QPushButton();

        part0->setObjectName("part0");
        part1->setObjectName("part1");
        part2->setObjectName("part2");
        part3->setObjectName("part3");
        part4->setObjectName("part4");

        part0->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "outline: none; "
            "image: url(:/icon/icon/partclose.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
            "QPushButton:pressed {"
            "image: url(:/icon/icon/partcloseclicked.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
        );

        part1->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "outline: none; "
            "image: url(:/icon/icon/part1.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
            "QPushButton:pressed {"
            "image: url(:/icon/icon/part1clicked.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
        );

        part2->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "outline: none; "
            "image: url(:/icon/icon/part2.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
            "QPushButton:pressed {"
            "image: url(:/icon/icon/part2clicked.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
        );

        part3->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "outline: none; "
            "image: url(:/icon/icon/part3.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
            "QPushButton:pressed {"
            "image: url(:/icon/icon/part3clicked.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
        );

        part4->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "outline: none; "
            "image: url(:/icon/icon/part4.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
            "QPushButton:pressed {"
            "image: url(:/icon/icon/part4clicked.png);"
            "width: 100px; "
            "height: 100px; "
            "}"
        );

        QLabel *spaceStepperLabel = new QLabel();
        spaceStepperLabel->setFixedHeight(70);
        Page3Layout->addWidget(spaceStepperLabel, 0, 0, Qt::AlignCenter | Qt::AlignBottom);
        Page3Layout->addWidget(part1, 1, 0, Qt::AlignTop);
        Page3Layout->addWidget(part2, 1, 1, Qt::AlignTop);
        Page3Layout->addWidget(part3, 1, 2, Qt::AlignTop);
        Page3Layout->addWidget(part4, 1, 3, Qt::AlignTop);
        Page3Layout->addWidget(part0, 1, 4, Qt::AlignTop);
        Page3Layout->addWidget(showStepperDIP, 2, 0, 1, 5, Qt::AlignCenter | Qt::AlignTop);
    }

  QWidget *Page1;
  QWidget *Page2;
  QWidget *Page3;

  QPushButton *topexit;

  servoDevice *servo;
  CircularProcess *round1;

  Painter *fan;
  QPushButton *fanButton;
  QPushButton *fanBackButton;
  QPushButton *fanStopButton;
  QTimer *timer;
  dcDevice *dc;

  stepperDevice* stepper;
  QThread *thread;
  QPushButton *part1;
  QPushButton *part2;
  QPushButton *part3;
  QPushButton *part4;
  QPushButton *part0;

  bool is180 = false;
  bool is0 = false;
};
#endif // WIDGET_H
