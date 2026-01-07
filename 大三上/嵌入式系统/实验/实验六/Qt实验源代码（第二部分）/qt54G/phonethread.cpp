#include "phonethread.h"

PhoneThread::PhoneThread()
{
    thread = new QThread;
    back = new MyBackend;

    back->moveToThread(thread);
    thread->start();
    connect(thread,&QThread::started,back,&MyBackend::getCall);
    connect(back, &MyBackend::callnumReceived, this, &PhoneThread::send, Qt::QueuedConnection);
    connect(back, &MyBackend::AnwerCalled, this, &PhoneThread::sendAnswer, Qt::QueuedConnection);
    connect(back, &MyBackend::NoCarrier, this, &PhoneThread::noCarrier, Qt::QueuedConnection);
    connect(back, &MyBackend::ModelLost, this, &PhoneThread::SendModelLost, Qt::QueuedConnection);
    connect(back, &MyBackend::SimLost, this, &PhoneThread::SendSimLost, Qt::QueuedConnection);
}

void PhoneThread::send(QString num)
{
    emit sendnum(num);
}

void PhoneThread::sendAnswer()
{
    qDebug()<<"sendanswer";
    emit sendanswer();
}

void PhoneThread::noCarrier()
{
//    qDebug()<<"behundup";
    emit behundup();
}

void PhoneThread::SendModelLost()
{
    emit sendmodellost();
}

void PhoneThread::SendSimLost()
{
    emit senlost();
}

PhoneThread* PhoneThread::instance() {
  static PhoneThread* obj = new PhoneThread;
  return obj;
}
