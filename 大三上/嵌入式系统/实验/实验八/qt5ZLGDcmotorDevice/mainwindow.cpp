#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentMotorState(Idle), key1Pressed(false), key2Pressed(false)
{
    // Setup Hardware
    motor = new dcDevice();
    motor->initDc();

    // Setup UI
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    keypad = new numKey(this);
    mainLayout->addWidget(keypad);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    btnClockwise = new QPushButton("Clockwise", this);
    btnClockwise->setFixedSize(100, 100);

    btnCounterClockwise = new QPushButton("CounterCW", this);
    btnCounterClockwise->setFixedSize(100, 100);

    btnStop = new QPushButton("Stop", this);
    btnStop->setFixedSize(100, 100);

    lblStatus = new QLabel("State: Idle", this);

    rightLayout->addWidget(btnClockwise);
    rightLayout->addWidget(btnCounterClockwise);
    rightLayout->addWidget(btnStop);
    rightLayout->addWidget(lblStatus);

    mainLayout->addLayout(rightLayout);

    connect(keypad->getButton(1), &QPushButton::clicked, this, &MainWindow::toggleClockwise);
    connect(keypad->getButton(2), &QPushButton::clicked, this, &MainWindow::toggleCounterClockwise);
    
    connect(btnClockwise, &QPushButton::clicked, this, [this](){
        if(currentMotorState != Clockwise) {
            currentMotorState = Clockwise;
            key1Pressed = true;
            key2Pressed = false;
            updateMotorHardware();
            updateIcons();
        }
    });
    connect(btnCounterClockwise, &QPushButton::clicked, this, [this](){
        if(currentMotorState != CounterClockwise) {
            currentMotorState = CounterClockwise;
            key1Pressed = false;
            key2Pressed = true;
            updateMotorHardware();
            updateIcons();
        }
    });
    connect(btnStop, &QPushButton::clicked, this, [this](){
        if(currentMotorState != Idle) {
            currentMotorState = Idle;
            key1Pressed = false;
            key2Pressed = false;
            updateMotorHardware();
            updateIcons();
        }
    });
    
    updateIcons();
}

MainWindow::~MainWindow()
{
    motor->closeDc();
    delete motor;
}

void MainWindow::toggleClockwise()
{
    if (currentMotorState == Clockwise) {
        currentMotorState = Idle;
        key1Pressed = false;
    } else {
        currentMotorState = Clockwise;
        key1Pressed = true;
        key2Pressed = false; 
    }
    updateMotorHardware();
    updateIcons();
}

void MainWindow::toggleCounterClockwise()
{
    if (currentMotorState == CounterClockwise) {
        currentMotorState = Idle;
        key2Pressed = false;
    } else {
        currentMotorState = CounterClockwise;
        key2Pressed = true;
        key1Pressed = false;
    }
    updateMotorHardware();
    updateIcons();
}

void MainWindow::updateMotorHardware()
{
    motor->controlDc(2); 
    switch (currentMotorState) {
    case Clockwise:
        motor->controlDc(0); 
        break;
    case CounterClockwise:
        motor->controlDc(1); 
        break;
    case Idle:
        motor->controlDc(2); 
        break;
    }
}

void MainWindow::updateIcons()
{
    switch (currentMotorState) {
    case Clockwise:
        lblStatus->setText("State: Clockwise");
        btnClockwise->setStyleSheet("background-color: green;");
        btnCounterClockwise->setStyleSheet("");
        btnStop->setStyleSheet("");
        keypad->getButton(1)->setStyleSheet("background-color: green;");
        keypad->getButton(2)->setStyleSheet("");
        break;
    case CounterClockwise:
        lblStatus->setText("State: CounterCW");
        btnClockwise->setStyleSheet("");
        btnCounterClockwise->setStyleSheet("background-color: green;");
        btnStop->setStyleSheet("");
        keypad->getButton(1)->setStyleSheet("");
        keypad->getButton(2)->setStyleSheet("background-color: green;");
        break;
    case Idle:
        lblStatus->setText("State: Idle");
        btnClockwise->setStyleSheet("");
        btnCounterClockwise->setStyleSheet("");
        btnStop->setStyleSheet("background-color: red;");
        keypad->getButton(1)->setStyleSheet("");
        keypad->getButton(2)->setStyleSheet("");
        break;
    }
}
