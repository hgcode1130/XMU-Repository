#ifndef LIS3DHTHREAD_H
#define LIS3DHTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "lis3dhdevice.h"

class Lis3dhThread : public QObject
{
    Q_OBJECT
public:
    explicit Lis3dhThread(QObject *parent = nullptr);
    static Lis3dhThread* instance();
public slots:
   Q_INVOKABLE void rotation180();
   Q_INVOKABLE void rotation0();
    Q_INVOKABLE void stopThread();
    Q_INVOKABLE void continueThread();

private:
    Lis3dhDevice*lis3dh;
    QThread *lis3dhthread;

signals:
    void turn180();
    void turn0();
signals:

};

#endif // LIS3DHTHREAD_H
