#ifndef SIGNALSLOTS_H
#define SIGNALSLOTS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class SIgnalSlots; }
QT_END_NAMESPACE

class SIgnalSlots : public QDialog
{
    Q_OBJECT

public:
    SIgnalSlots(QWidget *parent = nullptr);
    ~SIgnalSlots();

private:
    Ui::SIgnalSlots *ui;
private slots:
    void pushbutten_1_Slot();
    void pushbutten_2_Slot();
    void pushbutten_3_Slot();
};

#endif // SIGNALSLOTS_H
