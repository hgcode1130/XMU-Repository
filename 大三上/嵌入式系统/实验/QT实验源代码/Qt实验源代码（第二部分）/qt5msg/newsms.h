#ifndef NEWSMS_H
#define NEWSMS_H

#include <QWidget>
#include <QWidgetAction>
#include <QMargins>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include "syszuxpinyin.h"
#include <QRegularExpressionValidator>
#include <QDebug>
#include <qevent.h>
#include <QThread>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGuiApplication>
#include <QScreen>
#include "my_lineedit.h"
#include "my_textedit.h"
#include "lis3dhdevice.h"

class NewSmsCustomWidget;
class newsms : public QWidget
{
    Q_OBJECT
public:
    explicit newsms(QWidget *parent = nullptr);

    QPushButton *sendButton;
    QLabel *titlelabel;
    QVBoxLayout *layout;

    SyszuxPinyin *syszuxpinyin_sendphonenumber;
    SyszuxPinyin *syszuxpinyin_sendmessage;

    My_lineEdit *lineEdit_sendphonenumber;
    My_textEdit *textEdit_sendmessage;

    NewSmsCustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;
signals:
    void sendnewsms(QString contact,QString message);

private slots:
    void newsmsbackButtonClicked();
    void sendButtonClicked();
    void keyboardshow_sendphonenumber(QString data);
    void confirmString_sendphonenumber(QString gemfield);
    void keyboardshow_sendmessage(QString data);
    void confirmString_sendmessage(QString gemfield);
};


class NewSmsCustomWidget : public QWidget {
  Q_OBJECT
public:
  NewSmsCustomWidget(QWidget *parent = nullptr) {
      this->setObjectName("newSms");
      this->setStyleSheet("#newSms{background:white}");
      layout = new QVBoxLayout(this);
      bottomLayout = new QVBoxLayout;
      QHBoxLayout *horizontalLayout = new QHBoxLayout;
      QHBoxLayout  *lineHorizontalLayout = new QHBoxLayout;

      layout->setContentsMargins(0,0,0,0);
      bottomLayout->setContentsMargins(10,10,10,20);

      QWidget *topWidget = new QWidget(this);
      topWidget->setObjectName("topWidget");
      topWidget->setStyleSheet("#topWidget{background:rgb(240,242,244)}");
      topWidget->setLayout(horizontalLayout);
      newsmsbackButton = new QPushButton("取消",topWidget);
      QFont newsmsbackButtonFont("Noto Sans CJK SC Regular",25);
      newsmsbackButton->setFont(newsmsbackButtonFont);
      // 设置按钮的大小
      newsmsbackButton->setFixedSize(60, 60);
      // 设置按钮的样式表
      newsmsbackButton->setStyleSheet("QPushButton{background: transparent; border: none;color:#00BFFF;}"
                                      "QPushButton:pressed{color:#6495ED}");

      titlelabel = new QLabel(topWidget);
      QFont titlelabelfont("Noto Sans CJK SC Regular",25);
      titlelabel->setFont(titlelabelfont);
      titlelabel->setText("新信息");

      horizontalLayout->setContentsMargins(0,15,20,15);
      horizontalLayout->addStretch(6);
      horizontalLayout->addWidget(titlelabel,Qt::AlignHCenter);
      horizontalLayout->addStretch(3);
      horizontalLayout->addWidget(newsmsbackButton,Qt::AlignRight);
      layout->addWidget(topWidget);

      QLabel *lineLabel = new QLabel("收信人:",this);
      QFont lineLabelFont("Noto Sans CJK SC Regular",20);
      lineLabel->setFont(lineLabelFont);
      lineHorizontalLayout->addWidget(lineLabel);

      lineEdit_sendphonenumber =new My_lineEdit(this);
      lineEdit_sendphonenumber->setFocusPolicy(Qt::StrongFocus);
      lineEdit_sendphonenumber->setCursorPosition(0);
      lineEdit_sendphonenumber->setStyleSheet("QLineEdit{background: transparent; border: none;}");
      QFont lineEdit_sendphonenumberfont("Noto Sans CJK SC Regular",20);
      lineEdit_sendphonenumber->setFont(lineEdit_sendphonenumberfont);
      lineHorizontalLayout->addWidget(lineEdit_sendphonenumber);
      syszuxpinyin_sendphonenumber =new SyszuxPinyin();
      QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression("\\d{11}"), lineEdit_sendphonenumber);
      lineEdit_sendphonenumber->setValidator(validator);

      QFrame *lineFrame = new QFrame(this);
      lineFrame->setFrameShape(QFrame::HLine);
      lineFrame->setFrameShadow(QFrame::Sunken);

      layout->addLayout(lineHorizontalLayout);
      layout->addWidget(lineFrame);

      textEdit_sendmessage =new My_lineEdit();
      QFont textEdit_sendmessagefont("Noto Sans CJK SC Regular",25);
      textEdit_sendmessage->setStyleSheet("QLineEdit{border: 1px solid #c0c0c0;border-radius:15px;padding:5px}");
      textEdit_sendmessage->setFont(textEdit_sendmessagefont);
      textEdit_sendmessage->setPlaceholderText("Enter your message...");
      syszuxpinyin_sendmessage =new SyszuxPinyin();

      sendButton = new QPushButton(textEdit_sendmessage);
      QFont sendButtonfont("Noto Sans CJK SC Regular",20);
      sendButton->setFont(sendButtonfont);
      sendButton->setCursor(Qt::ArrowCursor);
      QWidgetAction * action = new QWidgetAction(textEdit_sendmessage);
      action->setDefaultWidget(sendButton);
      textEdit_sendmessage->addAction(action,QLineEdit::TrailingPosition);
      QIcon iconsend(":/send.png");
      sendButton->setIcon(iconsend);
      // 设置按钮的大小
      sendButton->setIconSize(QSize(60, 60));
      // 设置按钮的样式表
      sendButton->setStyleSheet("background: transparent; border: none; border-radius:15px");
      QMargins margins = textEdit_sendmessage->textMargins();
      textEdit_sendmessage->setTextMargins(margins.left(),margins.top(),sendButton->width(),margins.bottom());
      layout->addStretch(6);
      bottomLayout->addWidget(textEdit_sendmessage);
      layout->addLayout(bottomLayout);

      setLayout(layout);
  }
      QPushButton *newsmsbackButton;
      QPushButton *sendButton;
      QLabel *titlelabel;
      QVBoxLayout *layout;
      QVBoxLayout *bottomLayout;

      SyszuxPinyin *syszuxpinyin_sendphonenumber;
      SyszuxPinyin *syszuxpinyin_sendmessage;

      My_lineEdit *lineEdit_sendphonenumber;
      My_lineEdit *textEdit_sendmessage;
      bool is180 = false;
      bool is0 = false;
};

#endif // NEWSMS_H
