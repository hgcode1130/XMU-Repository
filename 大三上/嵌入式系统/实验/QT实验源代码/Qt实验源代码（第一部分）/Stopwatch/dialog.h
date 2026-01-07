#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "timerr.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    Timerr *timer;
private slots:
    void startSlot();
    void stopSlot();
};
#endif // DIALOG_H
