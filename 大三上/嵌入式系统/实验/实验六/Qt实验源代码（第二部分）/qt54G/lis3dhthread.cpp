#include "lis3dhthread.h"

Lis3dhThread::Lis3dhThread(QObject *parent) : QObject(parent)
{
    lis3dhthread = new QThread;
    lis3dh = new Lis3dhDevice;

    lis3dh->moveToThread(lis3dhthread);
    lis3dhthread->start();
    connect(lis3dhthread,&QThread::started,lis3dh,&Lis3dhDevice::run);
    connect(lis3dh, &Lis3dhDevice::stopthread, this, &Lis3dhThread::stopThread);
    connect(lis3dh, &Lis3dhDevice::change180, this, &Lis3dhThread::rotation180, Qt::QueuedConnection);
    connect(lis3dh, &Lis3dhDevice::change0, this, &Lis3dhThread::rotation0, Qt::QueuedConnection);
}

Lis3dhThread *Lis3dhThread::instance()
{
    static Lis3dhThread* obj = new Lis3dhThread;
    return obj;
}

void Lis3dhThread::rotation180()
{
    emit turn180();
}

void Lis3dhThread::rotation0()
{
    emit turn0();
}

void Lis3dhThread::stopThread()
{
    if(lis3dhthread->isRunning()){
        lis3dhthread->quit();
    }
    lis3dh->changeRunningState(false);
}

void Lis3dhThread::continueThread()
{
    if(lis3dhthread->isRunning()){
        lis3dhthread->start();
    }
    lis3dh->changeRunningState(true);
}
