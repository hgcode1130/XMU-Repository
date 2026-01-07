#ifndef TIMERR_H
#define TIMERR_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
namespace Ui {
class Timerr;
}

class Timerr : public QDialog
{
    Q_OBJECT

public:
    explicit Timerr(QWidget *parent = nullptr);
    ~Timerr();
    void start();
    void stop();
private:
    Ui::Timerr *ui;
    QTimer *timer; //定时器对象
    int timerBegin =0 ;
    int s =0;
    int ms =0;
    QString time;
public slots:
  void timeUpdateSlot();
};

#endif // TIMERR_H
