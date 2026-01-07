#ifndef EC20_H
#define EC20_H


extern "C"
{
    #include "hal_msg.h"
}
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QTimer>

class EC20: public QObject
{
  Q_OBJECT
public:
   EC20();
   Q_INVOKABLE int Call(char* phone_num);
   Q_INVOKABLE int answerCall();
   Q_INVOKABLE char *getcall();
   Q_INVOKABLE int handUp();
   Q_INVOKABLE QString getImei();

   enum Roles {
     IdRole = Qt::UserRole + 1,
     CallTypeRole,
     PhoneNumberRole,
     CallTimeRole,
     CallDurationRole
   };
signals:
   Q_INVOKABLE void modelLost();
};

class MyBackend : public QObject {
  Q_OBJECT

public:
 Q_INVOKABLE MyBackend();


signals:
  Q_INVOKABLE void AnwerCalled();
  Q_INVOKABLE void NoCarrier();
  Q_INVOKABLE void callnumReceived(const QString& num);
  Q_INVOKABLE void ModelLost();
  Q_INVOKABLE void SimLost();

public slots:
  Q_INVOKABLE void getCall();
  Q_INVOKABLE void sendModelLost();

private:
  EC20 *ec20;
  QTimer *timer;
};

#endif // EC20_H
