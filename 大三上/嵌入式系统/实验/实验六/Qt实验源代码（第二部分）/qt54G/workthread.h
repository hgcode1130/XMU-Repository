#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <ec20.h>
class workthread : public QObject
{
   Q_OBJECT
public:
    Q_INVOKABLE workthread();
    Q_INVOKABLE void send(QString num);
private:
    EC20*ec20;
    QThread *thread;
    MyBackend *back;
};

#endif // WORKTHREAD_H
