#ifndef SIGIN_H
#define SIGIN_H

#include <QDialog>

namespace Ui {
class Sigin;
}

class Sigin : public QDialog
{
    Q_OBJECT

public:
    explicit Sigin(QWidget *parent = nullptr);
    ~Sigin();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_sigin_confirm_clicked();

    void on_sigin_cancel_clicked();

private:
    Ui::Sigin *ui;
};

#endif // SIGIN_H
