#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTabBar>
#include <QStylePainter>
#include <QStyleOptionTab>
#include <QLabel>
#include <QScreen>
#include <QDebug>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QMovie>
#include <QThread>
#include <QThreadPool>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QScopedPointer>
#include "lis3dhdevice.h"
#include "mixadcdevice.h"
#include "lightled.h"
#include "customtabstyle.h"
#include "semicircular.h"
#include "lightelectric.h"
#include "temdevice.h"
#include "relaydevice.h"
#include "beepdevice.h"

class CustomWidget;
class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    //更新可燃气折线图
    void updateSeries(int data);

    //更新酒精提示灯
    void updateAlcoholLedState(int data);

    //更新火焰动图
    void updateFrameState(int data);

    //更新光照LCD
    void updateLightLCD(int data);

    ~Widget();

private:
    //beep
    beepDevice *beep;
    bool beepState = false;

    //ADC:酒精 可燃气 火焰
    mixAdcDevice *adc;

    QThreadPool* threadPool;

    //酒精
    lightLed *Alcohol;
    QLabel *alcoholText;

    //可燃气
    QChart *chart;
    QChartView *chartView;

    QValueAxis *axisX;
    QValueAxis *axisYLeft;

    int MAXX = 0;
    QLineSeries *gasSeries;

    //温度
    SemiCircular *temCircular;
    temDevice *tem;

    //继电器
    QLabel *relayLabel;
    QPushButton *relayButton;
    bool relayButtonState = false;
    relayDevice *relay;

    //光电
    QLabel *lightLabel;
    QLabel *lightLabelText;

    lightElectric *light;

    //火焰
    QLabel *frameLabel;
    QLabel *frameLabelText;
    QMovie *frameMovie;

    //蜂鸣器
    QPushButton *beepBtn;
    bool isBeepOn = false;

    //光照
    QLCDNumber *lightLCD;

    //退出
    QPushButton* exitButton;

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;

public slots:
    //当前页发生变化
    void handleIndexChange(int index);

    //接收adc发送的数据
    void recvData(int data);

    //处理继电器按钮
    void relayButtonClicked();

    //处理光电开关状态
    void handleLightElectricState(int state);

    //处理温度数据
    void updateCircular(float data);

    //Beep
    void beepBtnClicked();

    //exit
    void exitBtnClicked();

};


class CustomWidget : public QTabWidget {
  Q_OBJECT
public:
  CustomWidget(QWidget *parent = nullptr) : QTabWidget(parent) {
      QFont Widgetfont("Noto Sans CJK SC Regular",20);
      this->setFont(Widgetfont);
      //创建adc工具类对象以及对应线程
      adc = new mixAdcDevice();
      threadPool = new QThreadPool();

     // this->setFixedHeight(600);
      adc->openAdcDevice("A");
      adc->changeThreadState(true);
      threadPool->start(new ReadAdcDataTask(adc,"A"));

      this->setTabPosition(QTabWidget::West);
      this->tabBar()->setStyle(new CustomTabStyle);

      //添加页数
      QWidget *Page1 = new QWidget();
      QGridLayout *Page1Layout = new QGridLayout(Page1);

      QWidget *Page2 = new QWidget();
      QGridLayout *Page2Layout = new QGridLayout(Page2);

      QWidget *Page3 = new QWidget();
      QGridLayout *Page3Layout = new QGridLayout(Page3);

      QWidget *Page4 = new QWidget();
      QGridLayout *Page4Layout = new QGridLayout(Page4);

      QWidget *Page5 = new QWidget();
      QGridLayout *Page5Layout = new QGridLayout(Page5);

      QWidget *Page6 = new QWidget();
      QGridLayout *Page6Layout = new QGridLayout(Page6);

      QWidget *Page7 = new QWidget();
      QGridLayout *Page7Layout = new QGridLayout(Page7);

      QWidget *Page8 = new QWidget();
      QGridLayout *Page8Layout = new QGridLayout(Page8);

      QWidget *Page9 = new QWidget();
      QWidget *Page10 = new QWidget();
      QWidget *Page11 = new QWidget();
      QWidget *Page12 = new QWidget();
      QWidget *Page13 = new QWidget();
      QWidget *Page14 = new QWidget();

      exitButton = new QPushButton("退出");
      exitButton->setStyleSheet(
                  "QPushButton {"
                  "  color: rgb(255, 255, 255);"
                  "  background-color: rgb(76, 103, 153);"
                  "  border: none;"
                  "  outline: none;"
                  "  padding-top: 10px;"
                  "  padding-bottom: 10px;"
                  "  border-radius: 10px;"
                  "}"
                  "QPushButton:pressed {"
                  "  background-color: rgba(39, 67, 117);"
                  "  outline: none;"
                  "  border: none;"
                  "}"
      );

      QFont exitButtonfont("Noto Sans CJK SC Regular",20);
      exitButton->setFont(exitButtonfont);

      QFont tabBarfont("Noto Sans CJK SC Regular",20);
      this->tabBar()->setFont(tabBarfont);

      QIcon aolcholIcon(":/icon/icon/aolcholicon.png");
      QIcon gasIcon(":/icon/icon/gasicon.png");
      QIcon temIcon(":/icon/icon/temicon.png");
      QIcon relayIcon(":/icon/icon/relayicon.png");
      QIcon lightSwitchIcon(":/icon/icon/lightswitchicon.png");
      QIcon frameIcon(":/icon/icon/frameicon.png");
      QIcon beepIcon(":/icon/icon/beepicon.png");
      QIcon lightIcon(":/icon/icon/lighticon.png");

      // 添加选项卡
      this->addTab(Page1, aolcholIcon, "酒精");
      this->addTab(Page2, gasIcon, "可燃气");
      this->addTab(Page3, temIcon, "温度");
      this->addTab(Page4, relayIcon, "继电器");
      this->addTab(Page5, lightSwitchIcon, "光电");
      this->addTab(Page6, frameIcon, "火焰");
      this->addTab(Page7, beepIcon, "蜂鸣器");
      this->addTab(Page8, lightIcon, "光照");
      this->addTab(Page9, "");
      this->addTab(Page10, "");
      this->addTab(Page11, "");
      this->addTab(Page12, "");
      this->addTab(Page13, "");

      this->setTabEnabled(8, false);
      this->setTabEnabled(9, false);
      this->setTabEnabled(10, false);
      this->setTabEnabled(11, false);
      this->setTabEnabled(12, false);
      this->tabBar()->setTabButton(11, QTabBar::ButtonPosition::RightSide, exitButton);
      // 设置高度
      this->tabBar()->tabButton(11,QTabBar::ButtonPosition::RightSide)->setFixedSize(QSize(120,50));
      // 设置默认显示的选项卡
      this->setCurrentIndex(0);


      //酒精
      QLabel *showAlcoholDIP = new QLabel();
      QPixmap alcoholPixmap(":/icon/icon/aolcholBackground.png");

      double scaleFactor = 1;

      int newWidth = static_cast<int>(alcoholPixmap.width() * scaleFactor);
      int newHeight = static_cast<int>(alcoholPixmap.height() * scaleFactor);

      QPixmap scaledPixmap = alcoholPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
      showAlcoholDIP->setPixmap(scaledPixmap);

      int screenWidth = QApplication::primaryScreen()->geometry().width();
      int screenHeight = QApplication::primaryScreen()->geometry().height();

      // 计算宽度和高度
      int width = static_cast<int>(screenWidth * 0.273);
      int height = static_cast<int>(screenHeight * 0.583);

      int ledSize = 120;

      Alcohol = new lightLed(this);
      Alcohol->setLedSize(ledSize);
      Alcohol->setLedYPosition((height/2)-(ledSize-25));
      Alcohol->setLedXPosition(width/2);
      Alcohol->setFixedSize(width,height+20);
      Alcohol->setLedColor("green");
      Alcohol->setStyleSheet("border: none;background-color: transparent;");

      alcoholText = new QLabel("酒精浓度未超标");
      QFont alcoholfont("Noto Sans CJK SC Regular");
      alcoholText->setFont(alcoholfont);
      alcoholText->setFixedHeight(70);

      QLabel *alcoholSpace = new QLabel();
      alcoholSpace->setFixedHeight(100);

      QLabel *alcoholSpace1 = new QLabel();
      alcoholSpace1->setFixedHeight(100);

      Page1Layout->addWidget(alcoholSpace,0,0,Qt::AlignCenter|Qt::AlignTop);
      Page1Layout->addWidget(Alcohol,1,0,Qt::AlignCenter|Qt::AlignBottom);
      Page1Layout->addWidget(alcoholText,2,0,Qt::AlignCenter|Qt::AlignTop);
      Page1Layout->addWidget(alcoholSpace1,3,0,Qt::AlignCenter|Qt::AlignTop);
      Page1Layout->addWidget(showAlcoholDIP,4,0,Qt::AlignCenter|Qt::AlignTop);

      //可燃气
      QLabel *showGasDIP = new QLabel();
      QPixmap gasPixmap(":/icon/icon/gasBaground.png");

      double scaleFactorGas = 1;

      int newGasWidth = static_cast<int>(gasPixmap.width() * scaleFactorGas);
      int newGasHeight = static_cast<int>(gasPixmap.height() * scaleFactorGas);
      QPixmap scaledGasPixmap = gasPixmap.scaled(newGasWidth, newGasHeight, Qt::KeepAspectRatio);

      showGasDIP->setPixmap(scaledGasPixmap);

      //MAXX = 40;

      chart = new QChart();
      chartView = new QChartView(chart, this);
      chartView->setRenderHint(QPainter::Antialiasing);
      chartView->setFixedSize(newGasWidth, this->height()-newGasHeight+60);
      chartView->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

      QFont legendFont;
      legendFont.setFamily("Noto Sans CJK SC Regular");
      legendFont.setPointSize(18);

      chart->setBackgroundBrush(Qt::transparent);
      chart->legend()->setVisible(true);
      chart->legend()->setFont(legendFont);
      chart->setContentsMargins(0, 0, 0, 0);
      chart->setMargins(QMargins(0, 0, 0, 0));

      QFont chartFont;
      chartFont.setFamily("Noto Sans CJK SC Regular");
      chartFont.setPointSize(14);

      axisX = new QValueAxis;
      QFont xFont = axisX->labelsFont();
      xFont.setPointSize(12);
      axisX->setRange(0, 10);
      axisX->setGridLineVisible(false);
      chart->addAxis(axisX, Qt::AlignBottom);
      axisX->setLabelsFont(xFont);

      gasSeries = new QLineSeries();
      gasSeries->setName("可燃气");

      chart->addSeries(gasSeries);
      gasSeries->attachAxis(axisX);

      QBrush Leftbrush;
      Leftbrush.setStyle(Qt::SolidPattern);

      axisYLeft = new QValueAxis;
      QFont yLeftFont = axisYLeft->labelsFont();
      yLeftFont.setPointSize(12);
      axisYLeft->setRange(0,3000);
      axisYLeft->setGridLineVisible(false);
      axisYLeft->setTitleText("可燃气(mv)");
      axisYLeft->setTitleBrush(Leftbrush);
      axisYLeft->setTitleFont(yLeftFont);
      chart->addAxis(axisYLeft, Qt::AlignLeft);
      gasSeries->attachAxis(axisYLeft);
      axisYLeft->setLabelsFont(yLeftFont);

      // 设置标签的字体样式和颜色
      chart->legend()->setFont(chartFont);
      chart->setFont(chartFont);

      QLabel *chartViewSpace = new QLabel();
      chartViewSpace->setFixedHeight(60);

      QLabel *chartViewSpace1 = new QLabel();
      chartViewSpace1->setFixedHeight(60);

      Page2Layout->addWidget(chartViewSpace,0,0,Qt::AlignCenter);
      Page2Layout->addWidget(chartView,1,0,Qt::AlignCenter|Qt::AlignTop);
      Page2Layout->addWidget(chartViewSpace1,2,0,Qt::AlignCenter|Qt::AlignTop);
      Page2Layout->addWidget(showGasDIP,3,0,Qt::AlignCenter|Qt::AlignBottom);

      //温度
      tem = new temDevice();

      QLabel *showTemDIP = new QLabel();
      QPixmap temPixmap(":/icon/icon/temBackground.png");

      double scaleFactorTem = 1;

      int newTemWidth = static_cast<int>(gasPixmap.width() * scaleFactorTem);
      int newTemHeight = static_cast<int>(gasPixmap.height() * scaleFactorTem);
      QPixmap scaledTemPixmap = temPixmap.scaled(newTemWidth, newTemHeight, Qt::KeepAspectRatio);

      showTemDIP->setPixmap(scaledTemPixmap);

      temCircular = new SemiCircular;
      temCircular->setFixedSize(width*2,height*2);

      Page3Layout->addWidget(temCircular,0,0,Qt::AlignCenter|Qt::AlignTop);
      Page3Layout->addWidget(showTemDIP,2,0,Qt::AlignCenter|Qt::AlignBottom);

      //继电器
      relay = new relayDevice();

      relayLabel = new QLabel();
      relayButton = new QPushButton();
      relayButton->setText("打开");
      relayButton->setFixedSize(120,55);
      relayButton->setStyleSheet(
          "QPushButton {"
          "  color: rgb(0, 0, 0);"
          "  background-color: rgba(200, 200, 200, 0.5);"
          "  outline: none;"
          "  padding-top: 10px;"
          "  padding-bottom: 10px;"
          "  border-radius: 15px;"
          "}"
          "QPushButton:pressed {"
          "  color: rgb(255, 255, 255);"
          "  background-color: rgba(123, 123, 123, 0.5);"
          "  outline: none;"
          "}"
      );

      QFont relayButtonfont("Noto Sans CJK SC Regular",18);
      relayButton->setFont(relayButtonfont);
      QPixmap relayLabelPixmap(":/icon/icon/relay.png");

      QLabel *showRelaysDIP = new QLabel();
      QPixmap relayPixmap(":/icon/icon/relayBackground.png");

      double scaleFactorRelay = 1;

      int newRelayWidth = static_cast<int>(relayPixmap.width() * scaleFactorRelay);
      int newRelayHeight = static_cast<int>(relayPixmap.height() * scaleFactorRelay);


      QPixmap scaledRelayPixmap = relayPixmap.scaled(newRelayWidth, newRelayHeight, Qt::KeepAspectRatio);
      QPixmap scaledRelayLabelPixmap = relayLabelPixmap.scaled(150, 150, Qt::KeepAspectRatio);

      showRelaysDIP->setPixmap(scaledRelayPixmap);
      relayLabel->setPixmap(scaledRelayLabelPixmap);

      QLabel *relaySpace = new QLabel();
      relaySpace->setFixedHeight(80);

      QLabel *relaySpace1 = new QLabel();
      relaySpace1->setFixedHeight(60);

      Page4Layout->addWidget(relaySpace,0,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page4Layout->addWidget(relayLabel,1,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page4Layout->addWidget(relayButton,2,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page4Layout->addWidget(relaySpace1,3,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page4Layout->addWidget(showRelaysDIP,4,0,Qt::AlignHCenter|Qt::AlignBottom);

      //光电
      light = new lightElectric();

      lightLabel = new QLabel();
      QPixmap lightLabelPixmap(":/icon/icon/norlightswitch.png");

      QLabel *showLightsDIP = new QLabel();
      QPixmap lightPixmap(":/icon/icon/lightE.png");

      double scaleFactorLight = 1;

      int newLightWidth = static_cast<int>(lightPixmap.width() * scaleFactorLight);
      int newLightHeight = static_cast<int>(lightPixmap.height() * scaleFactorLight);


      QPixmap scaledLightPixmap = lightPixmap.scaled(newLightWidth, newLightHeight, Qt::KeepAspectRatio);
      QPixmap scaledLightLabelPixmap = lightLabelPixmap.scaled(200, 200, Qt::KeepAspectRatio);

      showLightsDIP->setPixmap(scaledLightPixmap);
      lightLabel->setPixmap(scaledLightLabelPixmap);

      lightLabelText = new QLabel("未检测遮挡");
      lightLabelText->setFixedHeight(70);

      QFont lightLabelfont("Noto Sans CJK SC Regular");
      lightLabelText->setFont(lightLabelfont);

      QLabel *lightSpace = new QLabel();
      lightSpace->setFixedHeight(70);

      QLabel *lightSpace1 = new QLabel();
      lightSpace1->setFixedHeight(60);

      Page5Layout->addWidget(lightSpace,0,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page5Layout->addWidget(lightLabel,1,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page5Layout->addWidget(lightLabelText,2,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page5Layout->addWidget(lightSpace1,3,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page5Layout->addWidget(showLightsDIP,4,0,Qt::AlignHCenter|Qt::AlignBottom);

      frameLabel = new QLabel(this);
      frameLabel->setFixedSize(300, 300);
      frameLabel->setScaledContents(true);

      QPixmap frameoffPixmap(":/icon/icon/frameoff.png");
      QPixmap scaledPixmapFrameOff = frameoffPixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
      frameLabel->setPixmap(scaledPixmapFrameOff);

      frameMovie = new QMovie(":/icon/icon/frame.gif");
      frameMovie->setScaledSize(frameLabel->size());

      QLabel *showFrameDIP = new QLabel();
      QPixmap framelPixmap(":/icon/icon/frame.png");

      double scaleFactorFrame = 1;

      int newFrameWidth = static_cast<int>(framelPixmap.width() * scaleFactorFrame);
      int newFrameHeight = static_cast<int>(framelPixmap.height() * scaleFactorFrame);

      QPixmap scaledFramePixmap = framelPixmap.scaled(newFrameWidth, newFrameHeight, Qt::KeepAspectRatio);
      showFrameDIP->setPixmap(scaledFramePixmap);

      frameLabelText = new QLabel("检测到火焰");
      frameLabelText->setFixedHeight(70);

      QFont frameLabelfont("Noto Sans CJK SC Regular");
      frameLabelText->setFont(frameLabelfont);

      QLabel *flameSpace = new QLabel();
      flameSpace->setFixedHeight(60);

      QLabel *flameSpace1 = new QLabel();
      flameSpace1->setFixedHeight(40);

      Page6Layout->addWidget(flameSpace1,0,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page6Layout->addWidget(frameLabel,1,0,Qt::AlignHCenter);
      Page6Layout->addWidget(frameLabelText,2,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page6Layout->addWidget(flameSpace,3,0,Qt::AlignHCenter|Qt::AlignBottom);
      Page6Layout->addWidget(showFrameDIP,4,0,Qt::AlignHCenter|Qt::AlignBottom);

      //蜂鸣器
      beep = new beepDevice();
      QLabel *showBeepeDIP = new QLabel();
      QPixmap beeplPixmap(":/icon/icon/beepBaground.png");

      double scaleFactorBeep = 1;

      int newBeepWidth = static_cast<int>(beeplPixmap.width() * scaleFactorBeep);
      int newBeepHeight = static_cast<int>(beeplPixmap.height() * scaleFactorBeep);

      QPixmap scaledBeepPixmap = beeplPixmap.scaled(newBeepWidth, newBeepHeight, Qt::KeepAspectRatio);
      showBeepeDIP->setPixmap(scaledBeepPixmap);

      QLabel * beepSpace = new QLabel();
      beepSpace->setFixedHeight(100);

      beepBtn = new QPushButton();
      beepBtn->setFixedSize(400,400);
      beepBtn->setStyleSheet("QPushButton { border: none; outline: none; }");
      beepBtn->setIcon(QIcon(":/icon/icon/beepoff.png"));
      beepBtn->setIconSize(QSize(400, 400));

      Page7Layout->addWidget(beepSpace,1,0,Qt::AlignHCenter);
      Page7Layout->addWidget(beepBtn,2,0,Qt::AlignHCenter|Qt::AlignTop);
      Page7Layout->addWidget(showBeepeDIP,3,0,Qt::AlignHCenter|Qt::AlignBottom);

      //光照
      lightLCD = new QLCDNumber();
      lightLCD->setDigitCount(8);
      lightLCD->setSegmentStyle(QLCDNumber::Flat);
      lightLCD->setFixedSize(650,300);
      lightLCD->setStyleSheet(
          "QLCDNumber {"
          "  background-color: black;"
          "  color: cyan;"
          "  border: 2px solid #555;"
          "  border-radius: 8px;"
          "  padding: 5px;"
          "}"
          "QLCDNumber::segment {"
          "  background-color: darkcyan;"
          "  color: cyan;"
          "}"
      );

      QLabel *showLighteDIP = new QLabel();
      QPixmap lightlPixmap(":/icon/icon/lightBackground.png");

      double scaleFactorLightLCD = 1;

      int newLightLCDWidth = static_cast<int>(lightlPixmap.width() * scaleFactorLightLCD);
      int newLightLCDHeight = static_cast<int>(lightlPixmap.height() * scaleFactorLightLCD);

      QPixmap scaledLightLCDPixmap = lightlPixmap.scaled(newLightLCDWidth, newLightLCDHeight, Qt::KeepAspectRatio);
      showLighteDIP->setPixmap(scaledLightLCDPixmap);

      QLabel * lightLCDSpace = new QLabel();
      lightLCDSpace->setFixedHeight(100);

      QLabel * lightLCDLeftSpace = new QLabel();
      lightLCDLeftSpace->setFixedWidth(70);

      QLabel * labelUnit = new QLabel("(mv)");
      QFont labelUnitfont("Noto Sans CJK SC Regular",80);
      labelUnit->setFont(labelUnitfont);

      QHBoxLayout *hlayout = new QHBoxLayout();
      hlayout->addWidget(lightLCD,Qt::AlignHCenter);
      hlayout->addWidget(labelUnit,Qt::AlignLeft);
      hlayout->setContentsMargins(150,0,0,0);

      Page8Layout->addWidget(lightLCDSpace,0,0,Qt::AlignHCenter);
      Page8Layout->addLayout(hlayout,1,0,Qt::AlignLeft | Qt::AlignBottom);
      Page8Layout->addWidget(showLighteDIP,2,0,Qt::AlignHCenter|Qt::AlignBottom);

  }

  //蜂鸣器
  QPushButton *beepBtn;
  beepDevice *beep;
  bool isBeepOn = false;
  bool beepState = false;

  //ADC:酒精 可燃气 火焰
  mixAdcDevice *adc;
  QThreadPool* threadPool;

  //酒精
  lightLed *Alcohol;
  QLabel *alcoholText;

  //可燃气
  QChart *chart;
  QChartView *chartView;

  QValueAxis *axisX;
  QValueAxis *axisYLeft;

  int count = 0;

  QLineSeries *gasSeries;

  //温度
  SemiCircular *temCircular;
  temDevice *tem;

  //继电器
  QLabel *relayLabel;
  QPushButton *relayButton;
  bool relayButtonState = false;
  relayDevice *relay;

  //光电
  QLabel *lightLabel;
  QLabel *lightLabelText;

  lightElectric *light;

  //火焰
  QLabel *frameLabel;
  QLabel *frameLabelText;
  QMovie *frameMovie;

  //光照
  QLCDNumber *lightLCD;

  //退出
  QPushButton* exitButton;
  bool is180 = false;
  bool is0 = false;

  QScopedPointer <ReadAdcDataTask> adcTask;
  QScopedPointer <ReadTemDataTask> temTask;
  QScopedPointer <ReadLightStateTask> lightTask;

};
#endif // WIDGET_H
