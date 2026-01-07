#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMessageBox>
#include <QDebug>
#include <QtMath>
#include <QFile>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QString openpath,QString savepath,QObject *parent = 0);

protected:
    virtual void run();
private:
    QString openpath;
    QString savepath;
signals:
    //signal
    void messageBoxSignal();
    void messageBoxInfoSignal();
    void progressBarSignal(int);
    void btnAble();
    void btnUnAble();
public slots:

};

#endif // MYTHREAD_H
