#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSqlDatabase database;
    void connectDb();
    void createTable();
    bool isStudentExist(int);
    int beforeId;
    int beforeAge;
    QString beforeName;
private slots:
    void btnInsterSlot();
    void btnDeleteSlot();
    void btnUpdateSlot();
    void btnSelectSlot();
};

#endif // DIALOG_H
