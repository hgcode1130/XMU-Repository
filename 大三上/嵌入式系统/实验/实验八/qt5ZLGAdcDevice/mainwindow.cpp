#include \
mainwindow.h\
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Setup UI
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    lblAdcValue = new QLabel(\ADC
Value:
0\, this);
    QFont font = lblAdcValue->font();
    font.setPointSize(24);
    lblAdcValue->setFont(font);
    lblAdcValue->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblAdcValue);

    // Initialize Hardware
    adc = new AdcDevice(); 
    display = new DisplayandMatrix();

    // Setup Timer (1000ms interval)
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
    timer->start(1000); // 1 second interval
}

MainWindow::~MainWindow()
{
    display->close();
    delete display;
    delete adc;
}

void MainWindow::onTimerTimeout()
{
    // Read ADC
    adc->ReadAdc();
    int val = adc->getVoltage(); // Assuming 0-1023

    // Update UI
    lblAdcValue->setText(QString(\ADC
Value:
%1\).arg(val));

    // Update Digitron
    display->showValue(val);
}
