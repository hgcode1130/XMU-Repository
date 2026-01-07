#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include \
adcdevice.h\
#include \displayandmatrix.h\

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimerTimeout();

private:
    QLabel *lblAdcValue;
    QTimer *timer;
    AdcDevice *adc;
    DisplayandMatrix *display;
};

#endif // MAINWINDOW_H
