#include "workerobject.h"

WorkerObject::WorkerObject()
{
    ec20 = new EC20();
}

void WorkerObject::answerCall() {
  ec20->answerCall();
}

void WorkerObject::handUp() {
    ec20->handUp();
}

int WorkerObject::call(QString phonenum)
{
    QString phoneNum = phonenum;
    QByteArray ba =  phoneNum.toLatin1();
    char* phone = ba.data();
    int ret = ec20->Call(phone);
    if(ret < 0)
    {
        return -1;
    }
    return 0;
}
