#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include "temdevice.h"
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QScreen>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include "lis3dhdevice.h"
#include "circularprocess.h"

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
    void updateTem(float data);
    void on_exit_clicked();

private:
    Ui::MainWindow *ui;
    QThread *myThread;

    QTimer *timer;

    temDevice *temhum;

    QChart *chart;

    QPushButton* ExitButton;

    CircularProcess *round1;

    QChartView *chartView;

    QValueAxis *axisX;
    QLineSeries *temSeries;
    QValueAxis *axisYLeft;

    int x;

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
        x = 0;

        QGridLayout* mainLayout = new QGridLayout();
        tem = new temDevice();

        // 创建图表部件
        chart = new QChart();
        chartView = new QChartView(chart, this);
        chartView->setRenderHint(QPainter::Antialiasing);
        mainLayout->addWidget(chartView, 1, 1, 5, 2);

        QFont chartfont("Noto Sans CJK SC Regular",20);
        chart->setFont(chartfont);

        QFont chartViewfont("Noto Sans CJK SC Regular",20);
        chartView->setFont(chartViewfont);

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QFont legendFont;
        legendFont.setFamily("Noto Sans CJK SC Regular");
        legendFont.setPointSize(20);

        chart->legend()->setVisible(true);
        chart->legend()->setFont(legendFont);
        chart->setContentsMargins(0, 0, 0, 0);
        chart->setMargins(QMargins(0, 0, 0, 0));

        QFont chartFont;
        chartFont.setFamily("Noto Sans CJK SC Regular");
        chartFont.setPointSize(20);

        axisX = new QValueAxis;
        QFont xFont("Noto Sans CJK SC Regular");
        xFont.setPointSize(20);
        axisX->setRange(0, 10);
        axisX->setGridLineVisible(false);
        chart->addAxis(axisX, Qt::AlignBottom);
        axisX->setLabelsFont(xFont);

        temSeries = new QLineSeries();
        temSeries->setName("温度");
        chart->addSeries(temSeries);
        temSeries->attachAxis(axisX);

        QBrush Leftbrush;
        Leftbrush.setStyle(Qt::SolidPattern);

        axisYLeft = new QValueAxis;
        QFont yLeftFont("Noto Sans CJK SC Regular");
        yLeftFont.setPointSize(20);
        axisYLeft->setRange(-45,45);
        axisYLeft->setGridLineVisible(false);
        axisYLeft->setTitleText("温度(℃)");
        axisYLeft->setTitleBrush(Leftbrush);
        axisYLeft->setTitleFont(yLeftFont);
        chart->addAxis(axisYLeft, Qt::AlignLeft);
        temSeries->attachAxis(axisYLeft);
        axisYLeft->setLabelsFont(yLeftFont);

        // 设置标签的字体样式和颜色
        chart->legend()->setFont(chartFont);

        // 获取屏幕的宽度和高度
        int screenWidth = QApplication::primaryScreen()->geometry().width();
        int screenHeight = QApplication::primaryScreen()->geometry().height();

        // 计算宽度和高度
        int width = static_cast<int>(screenWidth * 0.195);
        int height = static_cast<int>(screenHeight * 0.33);
        // 创建温度和湿度部件
        round1 = new CircularProcess(this);
        round1->setRange(-45, 45);
        round1->setFixedSize(width,height);
        //round1->setValue(temhum->temCollect(),"℃");
        round1->setStyleSheet("border: none;background-color: transparent;");

        QVBoxLayout* subLayout = new QVBoxLayout();
        QSpacerItem *spacer = new QSpacerItem(1, 140, QSizePolicy::Fixed, QSizePolicy::Fixed);
        subLayout->addItem(spacer);
        subLayout->addWidget(round1);
        subLayout->setContentsMargins(10,10,0,0);

        // 创建顶部标签和退出按钮
        ExitButton = new QPushButton(this);
        ExitButton->setStyleSheet("QPushButton { border: none; ""outline: none;""}");
        ExitButton->setIconSize(QSize(50, 50));
        ExitButton->setFixedSize(50, 50);
        QString topLabelStyle = "border: 1px solid transparent;background-color: white;";
        topLabel = new TopLabel("温度检测", ExitButton);
        topLabel->setStyleSheet(topLabelStyle);
        topLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        mainLayout->addWidget(topLabel, 0, 0, 1, 3, Qt::AlignTop);
        mainLayout->addLayout(subLayout, 1, 0);
        mainLayout->setContentsMargins(0,0,0,0);

        // 创建中心部件并设置布局
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(mainLayout);
        this->setCentralWidget(centralWidget);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }
  TopLabel *topLabel;
  temDevice *tem;

  QThread *myThread;

  QChart *chart;

  QPushButton* ExitButton;

  CircularProcess *round1;

  QChartView *chartView;

  QValueAxis *axisX;
  QLineSeries *temSeries;
  QValueAxis *axisYLeft;
  int x;

  bool is180 = false;
  bool is0 = false;
};
#endif // MAINWINDOW_H
