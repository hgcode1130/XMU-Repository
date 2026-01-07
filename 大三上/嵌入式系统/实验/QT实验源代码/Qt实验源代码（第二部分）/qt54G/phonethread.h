#ifndef PHONETHREAD_H
#define PHONETHREAD_H

#include <ec20.h>
class PhoneThread : public QObject
{
   Q_OBJECT
public:
    Q_INVOKABLE PhoneThread();
    Q_INVOKABLE void send(QString num);
    Q_INVOKABLE void sendAnswer();
    Q_INVOKABLE void noCarrier();
    Q_INVOKABLE void SendModelLost();
    Q_INVOKABLE void SendSimLost();
    static PhoneThread* instance();
private:
    EC20*ec20;
    QThread *thread;
    MyBackend *back;
signals:
    void sendnum(QString num);
    void sendanswer();
    void behundup();
    void sendmodellost();
    void senlost();
};

#endif // PHONETHREAD_H
