#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    customWidget = new CustomWidget();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    customWidget->resize(screenWidth, screenHeight);
    customWidget->showFullScreen();
    customWidget->topLabel->raise();

    //取消滑动条
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    proxyWidget = scene->addWidget(customWidget);
    proxyWidget->setTransformOriginPoint(proxyWidget->boundingRect().center());
    proxyWidget->setZValue(100);

    //开启线程进行三轴检测
    lis3dh = new Lis3dhDevice();
    thread3dh = new QThread();
    lis3dh->moveToThread(thread3dh);
    thread3dh->start();
    connect(thread3dh, &QThread::started, lis3dh, &Lis3dhDevice::run);
    connect(lis3dh, &Lis3dhDevice::stopthread, [&](){
        if(thread3dh->isRunning()){
            lis3dh->changeRunningState(false);
            thread3dh->quit();
        }
    });
    connect(lis3dh, &Lis3dhDevice::change180, [&](){
        if(!customWidget->is180){
            qDebug()<<"turn 180";
            this->view->rotate(180);
            update();
            customWidget->is180 = true;
            customWidget->is0 = true;
        }
    });
    connect(lis3dh, &Lis3dhDevice::change0, [&](){
        if(customWidget->is0){
            qDebug()<<"turn 0";
            this->view->rotate(180);
            update();
            customWidget->is180 = false;
            customWidget->is0 = false;
        }
    });

    updateThread = new UpdateThread(customWidget->myadc);
    updateThread->start();

    // 连接按钮的信号和槽函数
    connect(customWidget->myadc, SIGNAL(adcDataUpdated()), this, SLOT(printAdcData()));
    connect(customWidget->m_exitButton1, SIGNAL(clicked()), this, SLOT(on_exit_clicked()));

    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}

void MainWindow::on_exit_clicked()
{
    delete customWidget->myadc;
    if(updateThread->isRunning()){
        updateThread->quit();
    }
    this->close();
    QApplication::quit();
}

//获取到数据之后更新图表
void MainWindow::printAdcData()
{
    const float voltageValues = customWidget->myadc->getVoltage();
    customWidget->voltageLCD->display(voltageValues);
    customWidget->voltageProgressBar->setVoltage(voltageValues);
    customWidget->voltageSeries->append(customWidget->x, voltageValues);
    customWidget->x++;
    if (customWidget->x >= 10) {
        customWidget->chart->scroll(1, 0);
        customWidget->axisX->setRange(customWidget->x - 9, customWidget->x);
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete customWidget->myadc;
    delete customWidget->voltageProgressBar;
}


