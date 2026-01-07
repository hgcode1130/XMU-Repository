#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ledDvice.h"
#include <QtWidgets>
#include <QApplication>
#include <QMouseEvent>
#include <QScreen>
#include <QWidget>
#include <QTouchEvent>
#include <QDebug>
#include "lis3dhdevice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class CustomWidget;
class TopLabel;



class MainWindow : public QMainWindow {
    Q_OBJECT // 宏，启用 Qt 的元对象系统，包括信号和槽

private slots:
    // 槽函数，处理LED按钮点击事件
    void on_led1_clicked();
    void on_led2_clicked();
    void on_led3_clicked();
    void on_exit_clicked(); // 处理退出按钮点击事件

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CustomWidget *customWidget; // 旋转界面对象
    Lis3dhDevice *lis3dh;       // LIS3DH设备类实例
    QThread *thread3dh;         // 线程处理LIS3DH设备
    QGraphicsProxyWidget *proxyWidget; // 旋转界面代理部件
    QGraphicsView *view;        // 旋转界面视图部件
};




class TopLabel : public QWidget {
public:
    TopLabel(const QString& text, QPushButton* exit) : QWidget() {
        // 创建水平布局
        QHBoxLayout* layout = new QHBoxLayout;

        // 创建标签并设置文本
        QLabel* label = new QLabel(text);

        // 设置标签样式
        QString LabelStyle = "background-color: transparent";

        label->setFixedHeight(30);
        QFont font("Noto Sans CJK SC Regular", 25);
        label->setFont(font);
        label->setStyleSheet(LabelStyle);

        // 设置退出按钮图标
        QIcon exitIcon(":/icon/Icons/exit.png");
        exit->setIcon(exitIcon);

        // 将标签和退出按钮添加到布局中
        layout->addWidget(label);
        layout->addWidget(exit);

        // 设置标签和退出按钮的对齐方式
        layout->setAlignment(label, Qt::AlignLeft);
        layout->setAlignment(exit, Qt::AlignRight);

        // 设置布局
        setLayout(layout);
    }
};



class CustomWidget : public QMainWindow {
    Q_OBJECT // 启用 Qt 的元对象系统，包括信号和槽

public:
    CustomWidget(QWidget* parent = nullptr) : QMainWindow(parent) {
        QVBoxLayout* mainLayout = new QVBoxLayout(); // 主布局
        QWidget* centralWidget = new QWidget(this);  // 中心部件
        centralWidget->setLayout(mainLayout);
        centralWidget->setStyleSheet("background-color:#c8d0e1");

        // 实例化并初始化LED设备
        m_hqled = new ledDvice();
        // 网格布局用于放置LED控制按钮和标签
        QGridLayout* gridLayout = new QGridLayout();
        gridLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::MinimumExpanding), 1, 0);

        // 初始化LED标签
        Led1 = new QLabel("LED1熄灭");
        Led2 = new QLabel("LED2熄灭");
        Led3 = new QLabel("LED3熄灭");

        // 初始化控制按钮
        m_ledOnButton1 = new QPushButton(this);
        m_ledOnButton2 = new QPushButton(this);
        m_ledOnButton3 = new QPushButton(this);
        m_ledOnButton7 = new QPushButton(this);

        // 设置字体和按钮样式
        QFont LedFont("Noto Sans CJK SC Regular",20);
        Led1->setFont(LedFont);
        Led2->setFont(LedFont);
        Led3->setFont(LedFont);
        QString buttonStyle = "QPushButton { border: none; outline: none; }";
        m_ledOnButton1->setStyleSheet(buttonStyle);
        m_ledOnButton2->setStyleSheet(buttonStyle);
        m_ledOnButton3->setStyleSheet(buttonStyle);
        m_ledOnButton7->setStyleSheet(buttonStyle);

        // 设置按钮图标和大小
        m_ledOnButton1->setIcon(QIcon(":/icon/Icons/ledoff.png"));
        m_ledOnButton1->setIconSize(QSize(150, 150));
        m_ledOnButton1->setFixedSize(150, 150);

        m_ledOnButton2->setIcon(QIcon(":/icon/Icons/ledoff.png"));
        m_ledOnButton2->setIconSize(QSize(150, 150));
        m_ledOnButton2->setFixedSize(150, 150);

        m_ledOnButton3->setIcon(QIcon(":/icon/Icons/ledoff.png"));
        m_ledOnButton3->setIconSize(QSize(150, 150));
        m_ledOnButton3->setFixedSize(150, 150);


        m_ledOnButton7->setIconSize(QSize(50, 50));
        m_ledOnButton7->setFixedSize(50, 50);

        QSpacerItem* vspacer = new QSpacerItem(1, 160, QSizePolicy::Minimum, QSizePolicy::Minimum);
        gridLayout->addItem(vspacer, 0, 0);
        // 添加按钮和标签到网格布局
        gridLayout->addWidget(m_ledOnButton1, 1, 0);
        gridLayout->addWidget(m_ledOnButton2, 1, 1);
        gridLayout->addWidget(m_ledOnButton3, 1, 2);
        gridLayout->addWidget(Led1, 2, 0, Qt::AlignHCenter);
        gridLayout->addWidget(Led2, 2, 1, Qt::AlignHCenter);
        gridLayout->addWidget(Led3, 2, 2, Qt::AlignHCenter);

        // 创建并添加弹簧以调整布局空间
        QSpacerItem* spacer = new QSpacerItem(1, 260, QSizePolicy::Minimum, QSizePolicy::Minimum);
        gridLayout->addItem(spacer, 3, 0);

        // 创建顶部标签和设置样式
        QString topLabelStyle = "border: 1px solid transparent; background-color: white;";
        topLabel = new TopLabel("LED控制", m_ledOnButton7);
        topLabel->setStyleSheet(topLabelStyle);
        topLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        // 设置主布局的外边距为0，并添加顶部标签和网格布局
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addWidget(topLabel);
        mainLayout->addLayout(gridLayout);

        // 设置中央部件为窗口的中央部件
        this->setCentralWidget(centralWidget);
    }

    // 成员变量，存储LED状态和控制
    bool Led1State = false;
    bool Led2State = false;
    bool Led3State = false;

    QLabel *Led1;
    QLabel *Led2;
    QLabel *Led3;

    ledDvice *m_hqled;
    TopLabel* topLabel;

    QPushButton* m_ledOnButton1;
    QPushButton* m_ledOnButton2;
    QPushButton* m_ledOnButton3;
    QPushButton* m_ledOnButton7;

    bool is180 = false;
    bool is0 = false;
};

#endif // MAINWINDOW_H
