#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_login_cancel_clicked();
    void on_login_confirm_clicked();
    void on_iforget_linkHovered(const QString &link);
    void on_iforget_linkActivated(const QString &link);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
