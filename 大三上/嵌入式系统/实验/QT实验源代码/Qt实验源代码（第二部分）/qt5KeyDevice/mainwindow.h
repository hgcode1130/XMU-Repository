#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGraphicsDropShadowEffect>
#include <QScreen>
#include <QThread>
#include <QGuiApplication>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include "lis3dhdevice.h"
#include "keydevice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // 构造函数，初始化主窗口
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void changeKey(int keyStates);
    // 退出按钮的槽函数
    void on_exit_clicked();

private:
    Ui::MainWindow *ui;

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;
};

// 顶部标签类，包含退出按钮
class TopLabel : public QWidget {
public:
    TopLabel(const QString& text,QPushButton *exit) : QWidget() {
        QHBoxLayout* layout = new QHBoxLayout;
        QLabel* label = new QLabel(text);
        QString KeyLabelStyle = "background-color: transparent";

        QFont font("Noto Sans CJK SC", 25);
        label->setFont(font);
        label->setStyleSheet(KeyLabelStyle);

        QIcon exitIcon(":/icon/exit.png");
        exit->setIcon(exitIcon);

        layout->addWidget(label);
        layout->addWidget(exit);
        layout->setAlignment(label, Qt::AlignLeft);
        layout->setAlignment(exit, Qt::AlignRight);
        setLayout(layout);
    }
};

// 自定义窗口类
class CustomWidget : public QMainWindow {
    Q_OBJECT
public:
    CustomWidget(QWidget *parent = nullptr) : QMainWindow(parent) {
        key = new KeyDevice(); // 创建按键设备

        // 创建主画布
        QWidget *mainwidget = new QWidget(this);

        // 创建主布局以及次级布局
        QVBoxLayout* mainLayout = new QVBoxLayout(mainwidget);
        QHBoxLayout* hLayout = new QHBoxLayout(mainwidget);
        mainwidget->setLayout(mainLayout);

        // 创建退出按钮
        m_exitButton1 = new QPushButton(this);
        m_exitButton1->setStyleSheet("QPushButton { border: none; outline: none; }");
        m_exitButton1->setIconSize(QSize(50, 50));
        m_exitButton1->setFixedSize(50, 50);

        // 设置顶部标签样式
        QString topLabelStyle = "border: 1px solid transparent; border-radius: 5px; background-color: white;";
        topLabel = new TopLabel("按键功能检测", m_exitButton1);
        topLabel->setFixedHeight(100);
        topLabel->setStyleSheet(topLabelStyle);
        topLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        // 将顶部标签添加到主布局
        mainLayout->addWidget(topLabel, Qt::AlignTop);
        mainLayout->setContentsMargins(0, 0, 0, 0);

        // 创建放置Key和KeyText的垂直布局
        QVBoxLayout* VLayout1 = new QVBoxLayout();
        QVBoxLayout* VLayout2 = new QVBoxLayout();
        QFont font("Noto Sans CJK SC Regular", 20);

        // 创建按键和文本标签
        Key1 = new QLabel;
        Key2 = new QLabel;
        Key1Text = new QLabel("Key1未被按下");
        Key2Text = new QLabel("Key2未被按下");

        // 设置按键图标
        QPixmap keyPixmap(":/icon/Key_off.png");
        keyPixmap = keyPixmap.scaled(200,106);
        Key1->setPixmap(keyPixmap);
        Key1->setStyleSheet("border: none;");
        Key1Text->setFont(font);

        Key2->setPixmap(keyPixmap);
        Key2->setStyleSheet("border: none;");
        Key2Text->setFont(font);

        Key1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        Key2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        // 添加按键和文本标签到布局
        VLayout1->addStretch();
        VLayout1->addWidget(Key1);
        VLayout1->addWidget(Key1Text);
        VLayout1->addStretch();

        VLayout2->addStretch();
        VLayout2->addWidget(Key2);
        VLayout2->addWidget(Key2Text);
        VLayout2->addStretch();

        // 将垂直布局添加到水平布局
        hLayout->addStretch();
        hLayout->addLayout(VLayout1);
        hLayout->addStretch();
        hLayout->addLayout(VLayout2);
        hLayout->addStretch();

        // 将水平布局添加到主布局
        mainLayout->addLayout(hLayout);
        mainwidget->setLayout(mainLayout);
        setCentralWidget(mainwidget);
    }

    QTimer *mytimer;
    QLabel *Key1;
    QLabel *Key2;
    QLabel *Key1Text;
    QLabel *Key2Text;
    QPushButton *m_exitButton1;
    KeyDevice *key;
    TopLabel* topLabel;
    bool is180 = false;
    bool is0 = false;
};

#endif // MAINWINDOW_H
