#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include \
dcdevice.h\
#include \numkey.h\

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void toggleClockwise();
    void toggleCounterClockwise();
    void updateIcons();

private:
    // UI Elements
    numKey *keypad;
    QPushButton *btnClockwise;
    QPushButton *btnCounterClockwise;
    QPushButton *btnStop;
    QLabel *lblStatus; 

    // Hardware
    dcDevice *motor;
    void updateMotorHardware();

    // Logic State
    enum MotorState { Idle, Clockwise, CounterClockwise };
    MotorState currentMotorState;
    bool key1Pressed;
    bool key2Pressed;
};

#endif // MAINWINDOW_H
