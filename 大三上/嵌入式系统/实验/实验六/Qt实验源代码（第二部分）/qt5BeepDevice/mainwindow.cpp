#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    customWidget = new CustomWidget();  // 创建自定义Widget

    QScreen *screen = QGuiApplication::primaryScreen();  // 获取当前屏幕
    QRect screenGeometry = screen->geometry();  // 获取屏幕尺寸
    int screenWidth = screenGeometry.width();  // 屏幕宽度
    int screenHeight = screenGeometry.height();  // 屏幕高度

    customWidget->resize(screenWidth, screenHeight);  // 设置自定义Widget的大小为全屏
    customWidget->showFullScreen();  // 显示为全屏
    customWidget->topLabel->raise();  // 将顶部标签置于顶层

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // 水平滚动条禁用
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // 垂直滚动条禁用
    proxyWidget = scene->addWidget(customWidget);  // 将自定义Widget添加到场景中
    proxyWidget->setTransformOriginPoint(proxyWidget->boundingRect().center());  // 设置变换原点为中心
    proxyWidget->setZValue(100);  // 设置Z值为100

    lis3dh = new Lis3dhDevice();  // 创建Lis3dhDevice对象
    thread3dh = new QThread();  // 创建新线程
    lis3dh->moveToThread(thread3dh);  // 将lis3dh对象移至新线程
   // thread3dh->start();  // 启动线程

    // 连接信号与槽，当线程开始时，运行lis3dh的run函数
    connect(thread3dh, &QThread::started, lis3dh, &Lis3dhDevice::run);

    // 连接停止线程信号，确保线程安全退出
    connect(lis3dh, &Lis3dhDevice::stopthread, [&](){
        if(thread3dh->isRunning()){
            lis3dh->changeRunningState(false);  // 改变运行状态为false
            thread3dh->quit();  // 退出线程
        }
    });

    // 当设备旋转到180度时，调整视图和更新状态
    connect(lis3dh, &Lis3dhDevice::change180, [&](){
        if(!customWidget->is180){
            qDebug() << "turn 180";  // 输出旋转信息
            this->view->rotate(180);  // 视图旋转180度
            update();  // 更新界面
            customWidget->is180 = true;  // 标记为已旋转180度
            customWidget->is0 = true;
        }
    });

    // 当设备返回到0度时，恢复视图和更新状态
    connect(lis3dh, &Lis3dhDevice::change0, [&](){
        if(customWidget->is0){
            qDebug() << "turn 0";  // 输出返回信息
            this->view->rotate(180);  // 视图再次旋转180度，返回原位
            update();  // 更新界面
            customWidget->is180 = false;  // 标记为未旋转180度
            customWidget->is0 = false;
        }
    });

    // 连接按钮的信号和槽函数
      connect(customWidget->m_beepButton, SIGNAL(clicked()), this, SLOT(on_beep_clicked()));
      connect(customWidget->m_beepButton1, SIGNAL(clicked()), this, SLOT(on_exit_clicked()));

    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}


//根据标志位决定蜂鸣器开关
void MainWindow::on_beep_clicked()
{
    if(customWidget->beepState == false)
    {
        customWidget->beep->beepOn();
        customWidget->beepState = true;
        customWidget->m_beepButton->setIcon(QIcon(":/icon/beepmax.png"));
    }
    else
    {
        customWidget->beep->beepOff();
        customWidget->beepState = false;
        customWidget->m_beepButton->setIcon(QIcon(":/icon/beepoff.png"));
    }
}


void MainWindow::on_exit_clicked()
{
    this->close();
    QApplication::quit();
}


MainWindow::~MainWindow()
{
    delete customWidget->m_beepButton;
    delete customWidget->m_beepButton1;
    delete customWidget->beep;
}
