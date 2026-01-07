#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTimer>
#include <QScreen>
#include <QThread>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <alsa/asoundlib.h>
#include "audiorecorder.h"
#include "lis3dhdevice.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAudioRecorder;
class CustomWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_playmedia_clicked();

    void on_play_pausebt_clicked();

    void on_exit_clicked();

    void on_deletebt_clicked();

    void updateTime();


private:
    Ui::MainWindow *ui;
    QMap<QString,QString> fileMap;

    bool isplay = false;
    QTimer *myTimer;

    CustomWidget *customWidget;
    Lis3dhDevice *lis3dh;
    QThread *thread3dh;
    QGraphicsProxyWidget *proxyWidget;
    QGraphicsView *view;

signals:
    void stopTime();
};


class CustomWidget : public QMainWindow {
  Q_OBJECT
public:
    CustomWidget(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);  // 使用由 Qt Designer 生成的 UI 布局来初始化界面

        myRecord = new AudioRecorder();  // 创建音频录制器

        myPlay = new AudioRecorder();  // 创建音频录制器

        recordThread = new QThread();
        playThread = new QThread();
        // 初始化音频输入设备选择下拉菜单

        // 设置播放和录制按钮的图标和大小
        ui->play_pausebt->setIcon(QIcon(":/icon/icon/record.png"));
        ui->play_pausebt->setIconSize(QSize(60,60));
        ui->playmedia->setIcon(QIcon(":/icon/icon/play.png"));
        ui->playmedia->setIconSize(QSize(60,60));

        // 设置退出和删除按钮的图标和大小
        ui->exit->setIcon(QIcon(":/icon/icon/exit.png"));
        ui->exit->setIconSize(QSize(90,90));
        ui->deletebt->setIcon(QIcon(":/icon/icon/delete.png"));
        ui->deletebt->setIconSize(QSize(60,60));

        // 设置文本编辑框的文字换行模式
        ui->textEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

        QStringList audioFormat = {
            "wav",
            "mp3",
        };

        for(const QString &format : audioFormat){
            ui->input->addItem(format,QVariant(format));
        }

        // 读取家目录下的所有 .wav 文件并添加到播放文件列表中
        QDir dir("/home/linux/Videos");
        QStringList filter;
        filter<< "*.wav" << "*.mp3";
        QFileInfoList fileList = dir.entryInfoList(filter, QDir::Files);
        QString filename;
        foreach (const QFileInfo &file, fileList) {
            QString filename = file.fileName();
            QString filePath = file.absoluteFilePath();
            fileMap[filename] = filePath;  // 将文件名和文件路径存储在映射中
            qDebug()<<"filename"<<filename;
            ui->playfile->addItem(filename);  // 将文件名添加到播放文件列表下拉菜单
        }
    }

  Ui::MainWindow *ui;

  QMap<QString,QString> fileMap;
  AudioRecorder *myRecord = nullptr;
  AudioRecorder *myPlay = nullptr;

  QThread *recordThread = nullptr;
  QThread *playThread = nullptr;
  bool isRecrod = false;
  bool isplay = false;
  bool is180 = false;
  bool is0 = false;

};
#endif // MAINWINDOW_H
