#ifndef DCDEVICE_H
#define DCDEVICE_H

#include <QObject>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <QDebug>

#define IOCTL_MAGICDC 'D'
#define DC_MOTOR_ON _IO(IOCTL_MAGICDC, 0)
#define DC_MOTOR_OFF _IO(IOCTL_MAGICDC, 1)
#define DC_MOTOR_DIR _IOW(IOCTL_MAGICDC, 2, int)

class dcDevice : public QObject
{
    Q_OBJECT

public:
    dcDevice();
    void initDc();
    void controlDc(int operation);
    void closeDc();
    ~dcDevice();

private:
    int dcfd = 0;
};

#endif // DCDEVICE_H
