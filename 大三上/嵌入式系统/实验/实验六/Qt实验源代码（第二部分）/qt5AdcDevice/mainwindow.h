#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adcdevice.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QScreen>
#include <QGraphicsView>
#include "circularprogressbar.h"
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

public slots:
    void printAdcData();
    void on_exit_clicked();

private:
    Ui::MainWindow *ui;

    int maxDataPoints = 100;
    int x = 0;

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;

    UpdateThread* updateThread;
};


class TopLabel : public QWidget {
public:
    TopLabel(const QString& text,QPushButton *exit) : QWidget() {
        QHBoxLayout* layout = new QHBoxLayout;
        QLabel* label = new QLabel(text);
        QString LabelStyle = "background-color: transparent";
        QFont font("Noto Sans CJK SC Regular", 25);
        label->setFont(font);
        label->setStyleSheet(LabelStyle);

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
      myadc = new AdcDevice();
      this->setStyleSheet("background-color:#444444");
      // 创建布局
      QGridLayout* mainLayout = new QGridLayout();

      // 创建顶部标签
      m_exitButton1 = new QPushButton(this);
      m_exitButton1->setStyleSheet("QPushButton { border: none; outline: none; }");
      m_exitButton1->setIconSize(QSize(50, 50));
      m_exitButton1->setFixedSize(50, 50);

      QString topLabelStyle = "border: 1px solid transparent; background-color:rgb(139,134,130); color: white;";
      topLabel = new TopLabel("电位监测", m_exitButton1);
      topLabel->setStyleSheet(topLabelStyle);

      mainLayout->setContentsMargins(0, 0, 0, 0);
      mainLayout->addWidget(topLabel, 0, 0, 1, 3, Qt::AlignTop);

      QLabel* voltageLabel = new QLabel("电压(mV):", this);
      voltageLabel->setStyleSheet("color:white");
      QFont voltageLabelfont("Noto Sans CJK SC Regular", 18);
      voltageLabel->setFont(voltageLabelfont);

      // 创建数码管显示
      voltageLCD = new QLCDNumber(this);
      voltageLCD->setSegmentStyle(QLCDNumber::Flat);
      voltageLCD->display(0);
      voltageLCD->setStyleSheet("QLCDNumber { background-color: black; color: green; font-weight: bold; }");
      QFont voltageLCDfont("Noto Sans CJK SC Regular", 13);
      voltageLCD->setFont(voltageLCDfont);

      mainLayout->addWidget(voltageLabel, 1, 0);
      mainLayout->addWidget(voltageLCD, 2, 0);

      //创建电压显示圆环并且根据界面大小设置圆环大小
      voltageProgressBar = new Circularprogressbar(this);
      int width = static_cast<int>(QApplication::primaryScreen()->geometry().width() * 0.16);
      int height = static_cast<int>(QApplication::primaryScreen()->geometry().height() * 0.29);
      voltageProgressBar->setFixedSize(width, height);

      mainLayout->addWidget(voltageProgressBar, 5, 0);

      //创建图表
      chart = new QChart();
      chartView = new QChartView(chart);
      chartView->setRenderHint(QPainter::Antialiasing);
      chartView->setBackgroundBrush(QBrush(QColor(34, 36, 42)));
      QFont chartfont("Noto Sans CJK SC Regular",18);
      chart->setFont(chartfont);

      QFont chartViewfont("Noto Sans CJK SC Regular",18);
      chartView->setFont(chartViewfont);

      mainLayout->addWidget(chartView, 1, 1, 5, 2);

      QWidget* centralWidget = new QWidget(this);
      centralWidget->setLayout(mainLayout);
      setCentralWidget(centralWidget);

      QFont legendFont;
      legendFont.setFamily("Noto Sans CJK SC Regula");
      legendFont.setPointSize(18);

      voltageSeries = new QLineSeries();
      voltageSeries->setName("电压");
      chart->addSeries(voltageSeries);

      //图表样式
      chart->legend()->setVisible(true);
      chart->legend()->setFont(legendFont);
      chart->legend()->setColor(Qt::white);
      chart->legend()->setBrush(QBrush(Qt::white));
      chart->setContentsMargins(0, 0, 0, 0);
      chart->setMargins(QMargins(0, 0, 0, 0));
      chart->setBackgroundBrush(Qt::black);

      QFont chartFont;
      chartFont.setFamily("Noto Sans CJK SC Regul");
      chartFont.setPointSize(15);

      //设置X轴字体、范围、样式
      axisX = new QValueAxis;
      axisX->setRange(0, 10);
      QFont xFont("Noto Sans CJK SC Regular");
      xFont.setPointSize(15);
      axisX->setLabelsFont(xFont);
      axisX->setGridLineVisible(false);
      axisX->setLabelsColor(Qt::white);
      chart->addAxis(axisX, Qt::AlignBottom);
      voltageSeries->attachAxis(axisX);


      QBrush Lefbrush;
      Lefbrush.setStyle(Qt::SolidPattern);
      Lefbrush.setColor(Qt::white);

      //设置Y轴字体、范围、样式
      axisYLeft = new QValueAxis;
      QFont yLeftFont("Noto Sans CJK SC Regular");
      yLeftFont.setPointSize(15);
      axisYLeft->setLabelsColor(Qt::white);
      axisYLeft->setRange(0, 3000);
      axisYLeft->setGridLineVisible(false);
      axisYLeft->setTitleText("电压(mV)");
      axisYLeft->setTitleFont(yLeftFont);
      axisYLeft->setTitleBrush(Lefbrush);

      chart->addAxis(axisYLeft, Qt::AlignLeft);
      voltageSeries->attachAxis(axisYLeft);
      axisYLeft->setLabelsFont(yLeftFont);

      chart->legend()->setFont(chartFont);
      chart->legend()->setColor(Qt::white);
  }
  AdcDevice *myadc;

  QChart *chart;
  QChartView *chartView;

  QValueAxis  *axisX;

  QLineSeries *voltageSeries;
  QValueAxis *axisYLeft;

  QPushButton *m_exitButton1;

  QLCDNumber* voltageLCD;

  Circularprogressbar* voltageProgressBar;
  TopLabel* topLabel;

  bool is180 = false;
  bool is0 = false;

  int maxDataPoints = 100;
  int x = 0;
};
#endif // MAINWINDOW_H
