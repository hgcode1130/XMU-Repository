#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    customWidget = new CustomWidget(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    customWidget->resize(screenWidth, screenHeight);
    customWidget->showFullScreen();

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    proxyWidget = scene->addWidget(customWidget);
    proxyWidget->setTransformOriginPoint(proxyWidget->boundingRect().center());
    proxyWidget->setZValue(100);

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

    // 连接按钮的信号和槽函数
    connect(customWidget->ui->deletebt, &QPushButton::clicked, this, &MainWindow::on_deletebt_clicked);
    connect(customWidget->ui->exit, &QPushButton::clicked, this, &MainWindow::on_exit_clicked);

    connect(customWidget->ui->playmedia, &QPushButton::clicked, this, &MainWindow::on_playmedia_clicked);
    connect(customWidget->ui->play_pausebt, &QPushButton::clicked, this, &MainWindow::on_play_pausebt_clicked);

    customWidget->myRecord->moveToThread(customWidget->recordThread);
    customWidget->myPlay->moveToThread(customWidget->playThread);
    connect(this,&MainWindow::stopTime,[this](){
        myTimer->stop();
    });

    connect(customWidget->myPlay,&AudioRecorder::playEnd,[this](){
        emit stopTime();
        customWidget->playThread->quit();
        customWidget->isplay = false;
        customWidget->ui->playmedia->setIcon(QIcon(":/icon/icon/play.png"));
    });

    connect(customWidget->recordThread,&QThread::started,[this](){
        customWidget->myRecord->startRecording(customWidget->ui->input->currentText());
    });

    connect(customWidget->playThread,&QThread::started,[this](){
        customWidget->isplay = true;
        QString currentFile = customWidget->ui->playfile->currentText();
        if(currentFile == NULL) return;
        QString playFileName = QString("/home/linux/Videos/%1").arg(currentFile);
        customWidget->myPlay->startPlaying(playFileName);
    });

    myTimer = new QTimer(this);
    connect(myTimer,&QTimer::timeout,this,&MainWindow::updateTime);
    myTimer->start(100);
    // 设置 QGraphicsView 为中心控件或根据需要进行布局
    setCentralWidget(view);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_playmedia_clicked()
{
    if (customWidget->isRecrod) {
        qWarning() << "Cannot play while recording is active.";
        return;
    }
    if (!customWidget->isplay) {
        QString playfilename = customWidget->ui->playfile->currentText();
        QString filePath = customWidget->fileMap[playfilename];
        if (filePath.isEmpty()) {
            qWarning() << "No audio file path specified.";
            return;
        }
        myTimer->start(100);
        QString playMessage = tr("播放音频：%1\n").arg(playfilename);
        customWidget->ui->textEdit->insertPlainText(playMessage);
        customWidget->ui->playmedia->setIcon(QIcon(":/icon/icon/over.png"));
        customWidget->ui->label_4->setText("播放时长：");
        customWidget->isplay = true;
        customWidget->playThread->start();
    } else {
        myTimer->stop();
        customWidget->playThread->quit();
        customWidget->isplay = false;
        customWidget->ui->playmedia->setIcon(QIcon(":/icon/icon/play.png"));
    }
}

void MainWindow::on_play_pausebt_clicked()
{
    QString statusMessage;

    if (customWidget->isplay) {
        qWarning() << "Cannot record while playback is active.";
        return;
    }

    if (!customWidget->isRecrod) {

        myTimer->start(100);
        customWidget->ui->play_pausebt->setIcon(QIcon(":/icon/icon/over.png"));
        customWidget->ui->label_4->setText("录制时长：");

        customWidget->recordThread->start();
        statusMessage = tr("文件录制中\n");

        customWidget->isRecrod = true;
    } else {
        myTimer->stop();

        customWidget->ui->play_pausebt->setIcon(QIcon(":/icon/icon/record.png"));
        customWidget->myRecord->stopRecording();
        customWidget->recordThread->quit();
        customWidget->isRecrod = false;

        customWidget->fileMap[customWidget->myRecord->getPathName()] = customWidget->myRecord->getPath();  // 将文件名和文件路径存储在映射中
        customWidget->ui->playfile->addItem(customWidget->myRecord->getPathName());
        statusMessage = tr("停止录制\n");
    }

    customWidget->ui->textEdit->insertPlainText(statusMessage);
}


// 当删除按钮被点击时执行的函数
void MainWindow::on_deletebt_clicked()
{
    QString statusMessage = NULL;  // 初始化用于显示状态信息的字符串
    QString playfilename = customWidget->ui->playfile->currentText();  // 获取当前选择的文件名
    QString filePath = customWidget->fileMap.value(playfilename);  // 通过文件名获取文件的完整路径

    // 检查文件路径是否为空
    if (filePath.isEmpty()) {
        qWarning() << "No audio file path specified.";  // 如果路径为空，则输出警告
        statusMessage = tr("未指定音频文件路径\n");  // 设置状态消息为“未指定音频文件路径”
        customWidget->ui->textEdit->insertPlainText(statusMessage);
        return;  // 结束函数执行
    }

    QFile file(filePath);  // 使用文件路径创建 QFile 对象
    // 检查文件是否存在
    if (file.exists()) {
        bool success = file.remove();  // 尝试删除文件，并记录操作是否成功
        if (success) {
            customWidget->fileMap.remove(playfilename);  // 如果成功，从文件映射中移除文件条目
            customWidget->ui->playfile->removeItem(customWidget->ui->playfile->currentIndex());  // 在界面上移除文件选项
            qDebug() << playfilename + " has been successfully deleted.";  // 输出删除成功的调试信息
            statusMessage = tr("音频文件已成功删除\n");  // 设置状态消息为“音频文件已成功删除”
        } else {
            qWarning() << "Failed to delete " + playfilename;  // 如果删除失败，则输出警告
            statusMessage = tr("音频文件删除失败\n");  // 设置状态消息为“音频文件删除失败”
        }
    } else {
        qWarning() << "The file does not exist.";  // 如果文件不存在，则输出警告
        statusMessage = tr("文件不存在\n");  // 设置状态消息为“文件不存在”
    }

    customWidget->ui->time->setText("00:00");  // 将播放时间重置为 "00:00"
    customWidget->ui->textEdit->insertPlainText(statusMessage);  // 将状态消息显示在文本编辑区
}

void MainWindow::updateTime()
{
    if(customWidget->isRecrod){
//        qDebug()<<"customWidget->isRecrod";
        QString elapsedTime = customWidget->myRecord->getElapsedRecordingTime();
        customWidget->ui->time->setText(elapsedTime);
    }else if(customWidget->isplay){
//        qDebug()<<"customWidget->isplay";
        QString elapsedTime = customWidget->myPlay->getElapsedRecordingTime();
        customWidget->ui->time->setText(elapsedTime);
    }
}

void MainWindow::on_exit_clicked()
{
    this->close();
    QApplication::quit();
}

