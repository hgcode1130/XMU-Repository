#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QScreen>
#include <QThread>
#include <QFile>
#include "lis3dhdevice.h"
#include "rfiddevice.h"

namespace Ui {
class MainWindow;
}
class CustomWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void change_hf(QString hf);

    void change_lf(QString lf);

    void change_nfc(QString nfc);

    void change_915m(QString f915m);

    void change_2_4g(QString f2_4g);
    ~MainWindow();

public slots:
    void myslot_exit();

    void tabChange(int index);

    void modeChange();

private:
    Ui::MainWindow *ui;
    QTabWidget *mainwidget;
    QLabel *Hflabel;
    QLabel *Hfpixmap;

    QLabel *Lflabel;
    QLabel *Lfpixmap;

    QLabel *NFClabel;
    QLabel *NFCpixmap;

    QLabel *F915Mlabel;
    QLabel *F915Mpixmap;

    QLabel *label2_4G;
    QLabel *pixmap2_4G;
    RfidDevice *rfid;

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;
};
class CustomWidget : public QMainWindow {
  Q_OBJECT
public:
  CustomWidget(QWidget *parent = nullptr) : QMainWindow(parent) {

      //检查设备是CH还是M4

      bool check = checkCH_M4();

      rfid = new RfidDevice;// 创建 RFID 设备对象
      mainwidget = new QTabWidget(this);// 创建一个QTabWidget

      // 设置标签的样式
      mainwidget->setStyleSheet(
          "QTabBar::tab, QTabBar::tab:selected, QTabBar::tab:hover {"
          "  font: 12pt 'Noto Sans CJK SC Regular';"
          "  outline: none;"
          "  border: none;"
          "  border-top-left-radius: 8px;"
          "  border-top-right-radius: 8px;"
          "  width: 270px;"
          "  height: 50px;"
          "  color: rgb(102, 102, 102);"
          "  background-color: transparent;"
          "}"
          ""
          "QTabBar::tab:first {"
          "  margin-left: 2px;"
          "  outline: none;"
          "}"
          "QTabBar::tab:selected {"
          "  font-weight: bold;"
          "  background: #8F8FBD;"
          "  color: white;"
          "  outline: none;"
          "}"
          "QTabBar::tab:hover {"
          "  outline: none;"
          "}"
          "QTabBar::arrow {"
                  /* 改变箭头按钮的大小 */
                  "width: 10px;"
                  "height: 10px;"
                  /* 使用border来创建箭头 */
                  "border-style: solid;"
                  "border-width: 2px;"
                  "border-color: transparent transparent transparent #000;" /* 左侧箭头 */
              "}"

              "QTabBar::right-arrow {"
                  /* 改变右侧箭头按钮的大小 */
                  "width: 10px;"
                  "height: 10px;"
                  /* 使用border来创建箭头 */
                  "border-style: solid;"
                  "border-width: 2px;"
                  "border-color: transparent #000 transparent transparent;" /* 右侧箭头 */
              "}"
      );

      // 设置高频 (HF) 标签读取页
      QWidget *Hfwidget = new QWidget(mainwidget);// 创建高频标签页的容器
      QVBoxLayout *Hflayout = new QVBoxLayout(Hfwidget);// 垂直布局
      Hflabel = new QLabel("卡号: 00 00 00 00");// 标签显示
      Hfpixmap = new QLabel();// 显示图片
      QPixmap Hf(":/13.56M.png"); // 加载图片资源
      Hf.scaled(300,257); // 调整图片尺寸
      Hfpixmap->setPixmap(Hf);// 设置图片

      QFont Hflabelfont("Noto Sans CJK SC Regular",20);
      Hflabel->setFont(Hflabelfont);

      if(check){
          QLabel *showHfDIP = new QLabel(Hfwidget);
          QPixmap HfBackgroundPixmap(":/background.png");

          double HfScaleFactor = 1;

          int HfNewWidth = static_cast<int>(HfBackgroundPixmap.width() * HfScaleFactor);
          int HfNewHeight = static_cast<int>(HfBackgroundPixmap.height() * HfScaleFactor);

          QPixmap hfScaledPixmap = HfBackgroundPixmap.scaled(HfNewWidth, HfNewHeight, Qt::KeepAspectRatio);

          showHfDIP->setPixmap(hfScaledPixmap);

          Hflayout->addWidget(Hfpixmap,0,Qt::AlignCenter);
          Hflayout->addWidget(Hflabel,1,Qt::AlignCenter);
          Hflayout->addWidget(showHfDIP,2,Qt::AlignCenter);

      }else{
          QLabel* HfSpacer = new QLabel();
          HfSpacer->setFixedSize(QSize(1,100));

          Hflayout->addWidget(HfSpacer,0,Qt::AlignCenter);
          Hflayout->addWidget(Hfpixmap,1,Qt::AlignCenter);
          Hflayout->addWidget(Hflabel,2,Qt::AlignCenter);
      }

      Hflayout->setAlignment(Qt::AlignHCenter);
      Hflayout->setContentsMargins(0,55,0,55);

      QWidget *Lfwidget = new QWidget(mainwidget);
      QVBoxLayout *Lflayout = new QVBoxLayout(Lfwidget);
      Lflabel = new QLabel("卡号: 00 00 00 00 00",Lfwidget);
      Lfpixmap = new QLabel(Lfwidget);

      QFont Lflabelfont("Noto Sans CJK SC Regular",20);
      Lflabel->setFont(Lflabelfont);

      QPixmap Lf(":/125K.png");
      Lf.scaled(300,257);
      Lfpixmap->setPixmap(Lf);

      if(check){
          QLabel *showLfDIP = new QLabel(Lfwidget);
          QPixmap LfPixmap(":/background.png");

          double LfScaleFactor = 1;

          int LfNewWidth = static_cast<int>(LfPixmap.width() * LfScaleFactor);
          int LfNewHeight = static_cast<int>(LfPixmap.height() * LfScaleFactor);

          QPixmap lfScaledPixmap = LfPixmap.scaled(LfNewWidth, LfNewHeight, Qt::KeepAspectRatio);

          showLfDIP->setPixmap(lfScaledPixmap);

          Lflayout->addWidget(Lfpixmap,0,Qt::AlignCenter);
          Lflayout->addWidget(Lflabel,1,Qt::AlignCenter);
          Lflayout->addWidget(showLfDIP,2,Qt::AlignCenter);
      }else{
          QLabel* LfSpacer = new QLabel();
          LfSpacer->setFixedSize(QSize(1,100));

          Lflayout->addWidget(LfSpacer,0,Qt::AlignCenter);
          Lflayout->addWidget(Lfpixmap,1,Qt::AlignCenter);
          Lflayout->addWidget(Lflabel,2,Qt::AlignCenter);
      }
      Lflayout->setAlignment(Qt::AlignHCenter);
      Lflayout->setContentsMargins(0,55,0,55);
//NFC
      QWidget *NFCwidget = new QWidget(mainwidget);
      QVBoxLayout *NFClayout = new QVBoxLayout(NFCwidget);
      NFClabel = new QLabel("卡号: 00 00 00 00",NFCwidget);
      NFCpixmap = new QLabel(NFCwidget);

      QFont NFClabelfont("Noto Sans CJK SC Regular",20);
      NFClabel->setFont(NFClabelfont);

      QPixmap NFC(":/NFC.png");
      NFC.scaled(300,257);
      NFCpixmap->setPixmap(NFC);

      if(check){
          QLabel *showNFCDIP = new QLabel(NFCwidget);
          QPixmap NFCPixmap(":/background.png");

          double NFCScaleFactor = 1;

          int NFCNewWidth = static_cast<int>(NFCPixmap.width() * NFCScaleFactor);
          int NFCNewHeight = static_cast<int>(NFCPixmap.height() * NFCScaleFactor);

          QPixmap NFCScaledPixmap = NFCPixmap.scaled(NFCNewWidth, NFCNewHeight, Qt::KeepAspectRatio);

          showNFCDIP->setPixmap(NFCScaledPixmap);

          NFClayout->addWidget(NFCpixmap,0,Qt::AlignCenter);
          NFClayout->addWidget(NFClabel,1,Qt::AlignCenter);
          NFClayout->addWidget(showNFCDIP,2,Qt::AlignCenter);

      }else{
          QLabel* NFCSpacer = new QLabel();
          NFCSpacer->setFixedSize(QSize(1,100));

          NFClayout->addWidget(NFCSpacer,0,Qt::AlignCenter);
          NFClayout->addWidget(NFCpixmap,1,Qt::AlignCenter);
          NFClayout->addWidget(NFClabel,2,Qt::AlignCenter);
      }
      NFClayout->setContentsMargins(0,55,0,55);

      NFClayout->setAlignment(Qt::AlignHCenter);
     // NFClayout->setContentsMargins(0,100,0,30);

      // 设置高频 (915M) 标签读取页
      QWidget *F915Mwidget = new QWidget(mainwidget);// 创建高频标签页的容器
      QVBoxLayout *F915Mlayout = new QVBoxLayout(F915Mwidget);// 垂直布局
      F915Mlabel = new QLabel("卡号: 00 00 00 00",F915Mwidget);// 标签显示
      F915Mpixmap = new QLabel(F915Mwidget);// 显示图片
      QPixmap F915Mf(":/915M.png"); // 加载图片资源
      F915Mf.scaled(300,257); // 调整图片尺寸
      F915Mpixmap->setPixmap(F915Mf);// 设置图片

      QFont F915Mlabelfont("Noto Sans CJK SC Regular",20);
      F915Mlabel->setFont(F915Mlabelfont);

      if(check){
          QLabel *showF915MDIP = new QLabel(F915Mwidget);
          QPixmap F915MBackgroundPixmap(":/background.png");

          double F915MScaleFactor = 1;

          int F915MNewWidth = static_cast<int>(F915MBackgroundPixmap.width() * F915MScaleFactor);
          int F915MNewHeight = static_cast<int>(F915MBackgroundPixmap.height() * F915MScaleFactor);

          QPixmap F915MScaledPixmap = F915MBackgroundPixmap.scaled(F915MNewWidth, F915MNewHeight, Qt::KeepAspectRatio);

          showF915MDIP->setPixmap(F915MScaledPixmap);

          F915Mlayout->addWidget(F915Mpixmap,0,Qt::AlignCenter);
          F915Mlayout->addWidget(F915Mlabel,1,Qt::AlignCenter);
          F915Mlayout->addWidget(showF915MDIP,2,Qt::AlignCenter);

      }else{
          QLabel* F915MfSpacer = new QLabel();
          F915MfSpacer->setFixedSize(QSize(1,100));

          F915Mlayout->addWidget(F915MfSpacer,0,Qt::AlignCenter);

          F915Mlayout->addWidget(F915Mpixmap,1,Qt::AlignCenter);
          F915Mlayout->addWidget(F915Mlabel,2,Qt::AlignCenter);
      }

      F915Mlayout->setAlignment(Qt::AlignHCenter);
      F915Mlayout->setContentsMargins(0,55,0,55);

      // 设置高频 (2_4GM) 标签读取页
      QWidget *F2_4Gwidget = new QWidget(mainwidget);// 创建高频标签页的容器
      QVBoxLayout *F2_4Glayout = new QVBoxLayout(F2_4Gwidget);// 垂直布局
      label2_4G = new QLabel("卡号: 00 00 00 00");// 标签显示
      pixmap2_4G = new QLabel();// 显示图片
      QPixmap F2_4G(":/2.4G.png"); // 加载图片资源
      F2_4G.scaled(300,257); // 调整图片尺寸
      pixmap2_4G->setPixmap(F2_4G);// 设置图片

      QFont F2_4Glabelfont("Noto Sans CJK SC Regular",20);
      label2_4G->setFont(F2_4Glabelfont);

      if(check){
          QLabel *showF2_4GDIP = new QLabel(F2_4Gwidget);
          QPixmap F2_4GBackgroundPixmap(":/background.png");

          double F2_4GScaleFactor = 1;

          int F2_4GNewWidth = static_cast<int>(F2_4GBackgroundPixmap.width() * F2_4GScaleFactor);
          int F2_4GNewHeight = static_cast<int>(F2_4GBackgroundPixmap.height() * F2_4GScaleFactor);

          QPixmap F2_4GScaledPixmap = F2_4GBackgroundPixmap.scaled(F2_4GNewWidth, F2_4GNewHeight, Qt::KeepAspectRatio);

          showF2_4GDIP->setPixmap(F2_4GScaledPixmap);

          F2_4Glayout->addWidget(pixmap2_4G,0,Qt::AlignCenter);
          F2_4Glayout->addWidget(label2_4G,1,Qt::AlignCenter);
          F2_4Glayout->addWidget(showF2_4GDIP,2,Qt::AlignCenter);
      }else{
          QLabel* F2_4GSpacer = new QLabel();
          F2_4GSpacer->setFixedSize(QSize(1,100));

          F2_4Glayout->addWidget(F2_4GSpacer,0,Qt::AlignCenter);
          F2_4Glayout->addWidget(pixmap2_4G,1,Qt::AlignCenter);
          F2_4Glayout->addWidget(label2_4G,2,Qt::AlignCenter);
      }

      F2_4Glayout->setAlignment(Qt::AlignHCenter);
      F2_4Glayout->setContentsMargins(0,55,0,55);

      // 创建退出按钮
      exit = new QPushButton(this);
      exit->setStyleSheet("QPushButton { border: none;outline: none;}"); // 设置按钮样式
      exit->setIcon(QIcon(":/exit.png"));// 设置按钮图标
      exit->setIconSize(QSize(40, 40));// 设置图标尺寸

      QFont exitfont("Noto Sans CJK SC Regular");
      exit->setFont(exitfont);

      // 将不同的 RFID 标签读取页添加到标签容器
      mainwidget->addTab(Hfwidget,"RFID_13.56M");
      mainwidget->addTab(Lfwidget,"RFID_125K");
      mainwidget->addTab(F915Mwidget,"RFID_915M");
      mainwidget->addTab(NFCwidget,"RFID_NFC");
      mainwidget->addTab(F2_4Gwidget,"RFID_2_4G");
      mainwidget->setCornerWidget(exit);// 在标签页的角落放置退出按钮
      mainwidget->setCurrentIndex(0);// 设置默认显示的标签页

      rfid->func_init(F13_56M);// 初始化 RFID 设备
      mytimer = new QTimer(this);// 创建计时器
      mytimer->start(100);// 设置计时器

      setCentralWidget(mainwidget);
  }

  bool checkCH_M4(){
      QFile file("/dev/zlg72xx");
      return file.exists();
  }
  ~CustomWidget(){
      delete rfid;
      mytimer->stop();
      delete mytimer;
  }

  QTabWidget *mainwidget;
  QLabel *Hflabel;
  QLabel *Hfpixmap;

  QLabel *Lflabel;
  QLabel *Lfpixmap;

  QLabel *NFClabel;
  QLabel *NFCpixmap;

  QLabel *F915Mlabel;
  QLabel *F915Mpixmap;

  QLabel *label2_4G;
  QLabel *pixmap2_4G;
  RfidDevice *rfid;

  QPushButton *exit;
  QTimer *mytimer;

  bool is180 = false;
  bool is0 = false;
};
#endif // MAINWINDOW_H
