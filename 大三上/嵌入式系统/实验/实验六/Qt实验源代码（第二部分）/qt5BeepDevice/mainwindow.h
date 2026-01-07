#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QScreen>
#include <QGuiApplication>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QThread>
#include "beepdevice.h"
#include "lis3dhdevice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
   MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_beep_clicked();
    void on_exit_clicked();

private:
    Ui::MainWindow *ui;

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;
};

class TopLabel : public QWidget {
public:
    TopLabel(const QString& text,QPushButton *exit) : QWidget() {
        QHBoxLayout* layout = new QHBoxLayout;
        QLabel* label = new QLabel(text);
        QString BeepLabelStyle = "background-color: transparent";

        QFont font("Noto Sans CJK SC Regular", 20);
        label->setFont(font);
        label->setStyleSheet(BeepLabelStyle);

        QIcon exitIcon(":/icon/exit.png");
        exit->setIcon(exitIcon);

        layout->addWidget(label);
        layout->addWidget(exit);
        layout->setAlignment(label, Qt::AlignLeft);
        layout->setAlignment(exit, Qt::AlignRight);
        setLayout(layout);
    }
};

class CustomWidget : public QMainWindow {
  Q_OBJECT
public:
  CustomWidget(QWidget *parent = nullptr) : QMainWindow(parent) {
      beepState = false;
      QVBoxLayout* mainLayout = new QVBoxLayout(this);
      beep = new beepDevice();
      // 创建退出按钮
      m_beepButton1 = new QPushButton(this);
      m_beepButton1->setStyleSheet("QPushButton { border: none; ""outline: none;""}");
      m_beepButton1->setIconSize(QSize(50, 50));
      m_beepButton1->setFixedSize(50, 50);

      // 创建顶部标签
      QString topLabelStyle = "border: 1px solid transparent; background-color: white;";
      topLabel = new TopLabel("蜂鸣器控制", m_beepButton1);
      topLabel->setFixedHeight(100);
      topLabel->setStyleSheet(topLabelStyle);

      mainLayout->setContentsMargins(0,0,0,0);
      mainLayout->addWidget(topLabel , 0, Qt::AlignTop);
      mainLayout->addItem(new QSpacerItem(20,100,QSizePolicy::Minimum,QSizePolicy::Expanding));
      // 创建喇叭按钮
      m_beepButton = new QPushButton(this);
      m_beepButton->setStyleSheet("QPushButton { border: none; ""outline: none;""}");
      m_beepButton->setIcon(QIcon(":/icon/beepoff.png"));
      m_beepButton->setIconSize(QSize(500, 500));
      m_beepButton->setFixedSize(300, 300);
      mainLayout->addWidget(m_beepButton, 0, Qt::AlignHCenter);
      mainLayout->addItem(new QSpacerItem(20,100,QSizePolicy::Minimum,QSizePolicy::Expanding));

      QWidget* centralWidget = new QWidget(this);
      centralWidget->setLayout(mainLayout);

      setCentralWidget(centralWidget);
  }

  beepDevice *beep;
  QPushButton* m_beepButton;
  QPushButton* m_beepButton1;
  TopLabel* topLabel;

  bool beepState;
  Ui::MainWindow *ui;

  bool is180 = false;
  bool is0 = false;
};

#endif // MAINWINDOW_H
