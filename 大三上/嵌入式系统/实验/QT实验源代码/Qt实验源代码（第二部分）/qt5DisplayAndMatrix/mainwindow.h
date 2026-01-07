#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QThread>
#include <QTimer>
#include <QGridLayout>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include "lis3dhdevice.h"
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <string>
#include "numkey.h"
#include "displayandmatrix.h"

class ValueGetter;
class CustomWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void buttonexit();

    void numberButtonClicked(int num);

    void letterButtonClicked();

    void stopGettingValues();

private:
    QLCDNumber *Lcd;
    DisplayandMatrix *dm;
    QPushButton *m_exitButton1;
    QString accumulatedStr;
    ValueGetter* getter;
    QThread* thread;

    numKey *numKeys;

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;
};

class ValueGetter : public QObject {
    Q_OBJECT  // 使用 Qt 的信号和槽机制

public:
    // 构造函数
    ValueGetter(DisplayandMatrix* dm, QString* str, QLCDNumber* lcd)
    : dm(dm), accumulatedStr(str), lcd(lcd) {
        connect(this, &ValueGetter::quit, [=]{  // 连接退出信号到槽，用于停止运行
            isrunning = false;
        });
    }

    bool isrunning;  // 表示是否继续运行的标志

signals:
    void valueReceived(char value);  // 当接收到值时发出的信号
    void quit();  // 发出退出信号

private:
    DisplayandMatrix* dm;  // 指向显示和矩阵设备的指针
    QLCDNumber* lcd;  // 指向LCD显示器的指针
    QString *accumulatedStr;  // 指向累计字符串的指针

public slots:
    void run() {  // 运行槽，用于获取设备值的循环
        isrunning = true;
        while(isrunning) {  // 当 isrunning 为 true 时持续运行
            if(!isrunning) {
                qDebug()<<"break";  // 如果运行标志被置为 false，则打印信息并退出循环
                break;
            }
            char value = dm->getValue();  // 从设备获取一个字符值
            emit valueReceived(value);  // 发射 valueReceived 信号
            QThread::msleep(100);  // 暂停100毫秒
        }
    }

    void getValues(char value) {  // 处理接收到的值
        qDebug() << "value:" << value;  // 打印接收到的值
        QString strValue = QString(QChar(value));  // 将接收到的字符转换为QString
        *accumulatedStr += strValue;  // 将转换后的值追加到累计字符串中
        lcd->display(*accumulatedStr);  // 在LCD上显示累计字符串
        QThread::msleep(100);  // 暂停100毫秒
    }
};


class TopLabel : public QWidget {
public:
    // 构造函数，接受文本和退出按钮作为参数
    TopLabel(const QString& text, QPushButton *exit) : QWidget() {
        QHBoxLayout* layout = new QHBoxLayout;  // 水平布局管理器
        QLabel* label = new QLabel(text);  // 创建 QLabel 对象，并设置文本内容
        QString LabelStyle = "background-color: transparent";  // 设置标签样式
        QFont font("Noto Sans CJK SC Regular",25);  // 创建字体对象
        label->setFont(font);  // 应用字体到标签

        // 设置标签样式
        label->setStyleSheet(LabelStyle);

        // 将标签和退出按钮添加到水平布局中
        layout->addWidget(label);
        layout->addWidget(exit);

        // 设置布局到窗口
        setLayout(layout);
    }
};


class CustomWidget : public QMainWindow {
  Q_OBJECT
public:
  CustomWidget(QWidget *parent = nullptr) : QMainWindow(parent) {
      Lcd = new QLCDNumber(this);// 创建 LCD 数字显示器
      dm = new DisplayandMatrix();// 从工厂类创建矩阵键盘&数码管设备对象
      this->setStyleSheet("background-color:#111111"); // 设置窗口背景色

       // 创建退出按钮
      m_exitButton1 = new QPushButton(this);
      m_exitButton1->setIcon(QIcon(":/icon/exit.png"));
      m_exitButton1->setStyleSheet("QPushButton { border: none; ""outline: none;""}");
      m_exitButton1->setIconSize(QSize(50, 50));
      m_exitButton1->setFixedSize(50, 50);

      // 创建并设置顶部标签样式
      QString topLabelStyle = "border: 1px solid transparent;background-color:rgb(139,134,130);color : white;";
      TopLabel *topLabel = new TopLabel("数码管&矩阵按键", m_exitButton1);
      topLabel->setStyleSheet(topLabelStyle);
      topLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

      // 设置 LCD 的样式和参数
      QFont Lcdfont("Noto Sans CJK SC Regular");
      Lcd->setFont(Lcdfont);
      Lcd->setDigitCount(8);
      Lcd->setStyleSheet("QLCDNumber {"
                               "background-color: black;"
                               "color: red;"
                               "font-weight: bold;"
                               "border: 2px;"
                               "border-radius: 5px;"
                               "padding: 2px;"
                               "}"
                               "QLCDNumber::segment {"
                               "background-color: red;"
                               "border-radius: 2px;"
                               "}"
                               "QLCDNumber::decimal {"
                               "color: yellow;"
                               "}"
                               "QLCDNumber::zero {"
                               "color: orange;"
                               "}"
                               );

      //创建功能按钮
      AButton = new QPushButton("A");
      AButton->setFixedHeight(80);
      QFont AButtonfont("Noto Sans CJK SC Regular",20);
      AButton->setFont(AButtonfont);
      AButton->setStyleSheet("QPushButton {"
                            "background-color: #444444;"
                            "border: none;"
                            "color: white;"
                            "padding: 10px;"
                            "border-radius: 5px;"
                            "outline: none;"
                            "}"
                            "QPushButton:hover {"
                            "background-color: #555555;"
                            "outline: none;"
                            "}"
                            "QPushButton:pressed {"
                            "background-color: #666666;"
                            "outline: none;"
                            "}");
      //创建按钮布局
      QGridLayout *inputLayout = new QGridLayout();
      numKeys = new numKey(this);
      //创建数字按钮
      for (int i = 9; i >= 0; i--) {
          QPushButton *numberButton =numKeys->getButton(i);
          int row = (i - 1) / 3 + 1;
          int col = (i - 1) % 3 ;

          if(i==0){
            inputLayout->addWidget(numberButton, 4, 1);
          }else{
            inputLayout->addWidget(numberButton, row, col);
          }
      }
      inputLayout->setContentsMargins(30,0,30,20);
      BButton = new QPushButton("B", this);
      BButton->setFixedHeight(80);
      QFont BButtonfont("Noto Sans CJK SC Regular",20);
      BButton->setFont(BButtonfont);
      BButton->setStyleSheet("QPushButton {"
                                    "background-color: #444444;"
                                    "border: none;"
                                    "color: white;"
                                    "padding: 10px;"
                                    "border-radius: 5px;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #555555;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #666666;"
                                    "outline: none;"
                                    "}");

      CButton = new QPushButton("C",this);
      CButton->setFixedHeight(80);
      QFont CButtonfont("Noto Sans CJK SC Regular",20);
      CButton->setFont(CButtonfont);
      CButton->setStyleSheet("QPushButton {"
                                    "background-color: #444444;"
                                    "border: none;"
                                    "color: white;"
                                    "padding: 10px;"
                                    "border-radius: 5px;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #555555;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #666666;"
                                    "outline: none;"
                                    "}");

      DButton = new QPushButton("D",this);
      DButton->setFixedHeight(80);
      QFont DButtonfont("Noto Sans CJK SC Regular",20);
      DButton->setFont(DButtonfont);
      DButton->setStyleSheet("QPushButton {"
                                    "background-color: #444444;"
                                    "border: none;"
                                    "color: white;"
                                    "padding: 10px;"
                                    "border-radius: 5px;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #555555;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #666666;"
                                    "outline: none;"
                                    "}");

      EButton = new QPushButton("*",this);
      EButton->setFixedHeight(80);
      QFont EButtonfont("Noto Sans CJK SC Regular",20);
      EButton->setFont(EButtonfont);
      EButton->setStyleSheet("QPushButton {"
                                    "background-color: #444444;"
                                    "border: none;"
                                    "color: white;"
                                    "padding: 10px;"
                                    "border-radius: 5px;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #555555;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #666666;"
                                    "outline: none;"
                                    "}");

      FButton = new QPushButton("#",this);
      FButton->setFixedHeight(80);
      QFont FButtonfont("Noto Sans CJK SC Regular",20);
      FButton->setFont(FButtonfont);
      FButton->setStyleSheet("QPushButton {"
                                    "background-color: #444444;"
                                    "border: none;"
                                    "color: white;"
                                    "padding: 10px;"
                                    "border-radius: 5px;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #555555;"
                                    "outline: none;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #666666;"
                                    "outline: none;"
                                    "}");
      //在布局中放置控件
      inputLayout->addWidget(AButton, 1, 3);
      inputLayout->addWidget(BButton, 2, 3);
      inputLayout->addWidget(CButton, 3, 3);
      inputLayout->addWidget(DButton, 4, 3);
      inputLayout->addWidget(FButton, 4, 2);
      inputLayout->addWidget(EButton, 4, 0);

      // 创建总布局
      QVBoxLayout *mainlayout = new QVBoxLayout();
      QWidget *mainwidget = new QWidget();
      mainlayout->addWidget(topLabel,Qt::AlignTop);
      mainlayout->addWidget(Lcd);
      mainlayout->addLayout(inputLayout);
      mainlayout->setContentsMargins(0,0,0,10);
      mainwidget->setLayout(mainlayout);
      setCentralWidget(mainwidget);
     // timer->start();

      // 配置并启动后台线程以处理数据获取
      getter = new ValueGetter(dm, &accumulatedStr, Lcd);
      thread = new QThread(this);
      getter->moveToThread(thread);

      connect(getter, &ValueGetter::valueReceived, getter,&ValueGetter::getValues);
      connect(thread, &QThread::started, getter, &ValueGetter::run);
      thread->start();
      if(thread->isRunning())
      {
          qDebug()<<"thread is Running";
      }
  }
  QLCDNumber *Lcd;
  DisplayandMatrix *dm;
  QPushButton *m_exitButton1;
  QString accumulatedStr;
  ValueGetter* getter;
  QThread* thread;

  numKey *numKeys;

  QPushButton *AButton;
  QPushButton *BButton;
  QPushButton *CButton;
  QPushButton *DButton;
  QPushButton *EButton;
  QPushButton *FButton;

  bool is180 = false;
  bool is0 = false;
};
#endif // MAINWINDOW_H
