#ifndef SMS_H
#define SMS_H

#include <QWidget>
#include <QWidgetAction>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include "syszuxpinyin.h"
#include <QRegularExpressionValidator>
#include <QDebug>
#include <QThread>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QTextBrowser>
#include <QListWidget>
#include <QMargins>
#include "lis3dhdevice.h"
#include "my_lineedit.h"
#include "chatlabel.h"
class SmsCustomWidget;
class sms : public QWidget
{
    Q_OBJECT
public:
    explicit sms(QWidget *parent = nullptr);
    QLabel *titleLabel;
    QTextBrowser *textEdit;

    My_lineEdit *lineEdit_sendsms;
    SyszuxPinyin *syszuxpinyin_sendsms;

    SmsCustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;

    int lastItemPosition = 0;

signals:
    void sendsms(QString contact,QString message);
public slots:
    void sendsmsButtonClicked();
    void backButtonClicked();
    void myslotgetphone(QString,QString);
    void keyboardshow_sendsms(QString data);
    void confirmString_sendsms(QString gemfield);
};
class SmsCustomWidget : public QWidget {
  Q_OBJECT
public:
  SmsCustomWidget(QWidget *parent = nullptr) {
      this->setObjectName("sms");
      this->setStyleSheet("#sms{background:white}");
      bottomLayout = new QVBoxLayout;
      QHBoxLayout *horizontalLayout = new QHBoxLayout;
      //QHBoxLayout  *lineHorizontalLayout = new QHBoxLayout;

      QWidget *topWidget = new QWidget(this);
      topWidget->setObjectName("topWidget");
      topWidget->setStyleSheet("#topWidget{background:rgb(240,242,244)}");
      topWidget->setLayout(horizontalLayout);

      backButton = new QPushButton(this);
      QIcon iconback(":/back.png");
      backButton->setIcon(iconback);
      backButton->setIconSize(QSize(60, 60));
      // 设置按钮的样式表
      backButton->setStyleSheet("background: transparent; border: none;");

      titleLabel = new QLabel("");
      QFont titleLabelfont("Noto Sans CJK SC Regular",25);
      titleLabel->setFont(titleLabelfont);

      backButton->setFixedSize(60, 60);
      horizontalLayout->addWidget(backButton);
      horizontalLayout->addStretch(4);
      horizontalLayout->addWidget(titleLabel,Qt::AlignHCenter);
      horizontalLayout->addStretch(3);
      horizontalLayout->setContentsMargins(15,15,20,15);

      // 创建垂直布局，包含文本编辑框
      QVBoxLayout *verticalLayout = new QVBoxLayout;

      textEdit = new QTextEdit;
      QFont textEditfont("Noto Sans CJK SC Regular",20);
      textEdit->setFont(textEditfont);
      QPalette pal = textEdit->palette();
      pal.setBrush(QPalette::Base,QBrush(Qt::transparent));
      textEdit->setPalette(pal);

      textEdit->setStyleSheet("QTextEdit{background: transparent; border: none;}");

      textEdit->setWindowFlags(Qt::FramelessWindowHint | textEdit->windowFlags());
      textEdit->setAttribute(Qt::WA_TranslucentBackground);

      list = new QListWidget();
      list->setStyleSheet("QListWidget{background: transparent; border: none;}");
      list->setResizeMode(QListView::Adjust);
      list->setSortingEnabled(false);
      verticalLayout->addWidget(list);

      // 创建水平布局，包含文本框和发送按钮
      QHBoxLayout *bottomLayout = new QHBoxLayout;

      //QLineEdit *lineEdit = new QLineEdit;

      lineEdit_sendsms =new My_lineEdit();
      lineEdit_sendsms->setStyleSheet("QLineEdit{border: 1px solid #c0c0c0;border-radius:15px;padding:5px}");
      QFont lineEdit_sendsmsfont("Noto Sans CJK SC Regular",25);
      lineEdit_sendsms->setFont(lineEdit_sendsmsfont);
      lineEdit_sendsms->setPlaceholderText("fill your message...");
      syszuxpinyin_sendsms =new SyszuxPinyin();
      sendsmsButton = new QPushButton(lineEdit_sendsms);
      sendsmsButton->setCursor(Qt::ArrowCursor);
      QWidgetAction * action = new QWidgetAction(lineEdit_sendsms);
      action->setDefaultWidget(sendsmsButton);
      lineEdit_sendsms->addAction(action,QLineEdit::TrailingPosition);
      QIcon iconsend(":/send.png");
      sendsmsButton->setIcon(iconsend);
      // 设置按钮的大小
      sendsmsButton->setIconSize(QSize(60, 60));
      // 设置按钮的样式表
      sendsmsButton->setStyleSheet("background: transparent; border: none; border-radius:15px");
      QMargins margins = lineEdit_sendsms->textMargins();
      lineEdit_sendsms->setTextMargins(margins.left(),margins.top(),sendsmsButton->width(),margins.bottom());
      bottomLayout->addWidget(lineEdit_sendsms);
      bottomLayout->setContentsMargins(10,10,10,20);
      verticalLayout->addLayout(bottomLayout);

      // 创建主布局，包含水平和垂直布局
      QVBoxLayout *mainLayout = new QVBoxLayout;
      mainLayout->setContentsMargins(0,0,0,0);
      verticalLayout->setContentsMargins(0,0,0,0);

      mainLayout->addWidget(topWidget);
      mainLayout->addLayout(verticalLayout);

      // 设置主窗口的布局
      setLayout(mainLayout);
  }
      QVBoxLayout *bottomLayout;
      QListWidget *list = nullptr;
      QLabel *titleLabel;
      QTextEdit *textEdit;
      QPushButton *sendsmsButton;
      QPushButton *backButton;
      My_lineEdit *lineEdit_sendsms;
      SyszuxPinyin *syszuxpinyin_sendsms;
      bool is180 = false;
      bool is0 = false;
};
#endif // SMS_H
