#ifndef STARTEXE_H
#define STARTEXE_H

#include <QWidget>
#include <QProcess>
QT_BEGIN_NAMESPACE
namespace Ui { class StartExe; }
QT_END_NAMESPACE

class StartExe : public QWidget
{
    Q_OBJECT

public:
    StartExe(QWidget *parent = nullptr);
    ~StartExe();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::StartExe *ui;
};
#endif // STARTEXE_H
