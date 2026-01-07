#ifndef LIS3DHDEVICE_H
#define LIS3DHDEVICE_H

#include <QObject>
#include <cmath>

class Lis3dhDevice : public QObject
{
    Q_OBJECT
public:
    Lis3dhDevice();
    ~Lis3dhDevice();
    static int filter(const struct dirent *entry);
    int openAccelDeviceXYZ(int &adcxfd_x, int &adcxfd_y, int &adcxfd_z, QString function);
    int readDeviceValue(int fd, QString &value);
    int readAccelValues(int adcxfd_x, int adcxfd_y, int adcxfd_z);
    void run();
    void changeRunningState(bool state);

private:
    bool runningState = true;
    QString xValue;
    QString yValue;
    QString zValue;
signals:
    void change180();
    void change0();
    void stopthread();
};

#endif // LIS3DHDEVICE_H
