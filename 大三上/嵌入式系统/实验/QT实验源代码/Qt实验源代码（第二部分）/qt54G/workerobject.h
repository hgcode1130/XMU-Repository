#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H

#include <QObject>
#include "ec20.h"
class WorkerObject : public QObject
{
  Q_OBJECT

public:
 Q_INVOKABLE  WorkerObject();
 Q_INVOKABLE void answerCall();
 Q_INVOKABLE void handUp();
 Q_INVOKABLE int call(QString phonenum);
private:
  EC20*ec20;

signals:
  void finished();

};

#endif // WORKEROBJECT_H
