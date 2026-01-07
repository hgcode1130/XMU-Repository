#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QFile>
#include <QString>
#include <QPainter>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QMouseEvent>
#include <QParallelAnimationGroup>
#include "photoview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void loadImage();
    void recvImage();
    bool eventFilter(QObject*watched,QEvent*event) override;

    ~MainWindow();

private slots:
    void updateFrame();

    void on_getPhoto_clicked();

    void on_exit_clicked();

    void openPhotoView();

    void openMainWindow();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    QTimer *timer;
    cv::Mat frame;
    photoView *photoview;
};

#endif // MAINWINDOW_H
