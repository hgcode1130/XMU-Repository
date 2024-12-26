#include "login.h"
#include "ui_login.h"
#include "base.h"
#include "mysql.h"
#include "main.h"
#include "welcom.h"
#include "mymap.h"
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
   // setAttribute(Qt::WA_DeleteOnClose);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_cancel_clicked()
{
    close();
}

void Login::on_login_confirm_clicked()
{

    QString username = ui->login_username->text();
    QString passwd = ui->login_passwd->text();
    if (!check_string(username) || !check_string(passwd)){
        qDebug() << "非法输入!";
        ui->login_notice->setText("请输入字母、数字或下划线以内字符！");
        widgetShake(this,5);
        return;
    }
    if(passwd.length() == 0){
        ui->login_notice->setText("请输入密码!");
        widgetShake(this,5);
        return;
    }
    MySQL sql ;
    QString get_passwd = sql.get_user_passwd(username);
    if (get_passwd.length() == 0){
        ui->login_notice->setText("用户不存在!");
        widgetShake(this,5);
    }else if(QString::compare(get_passwd,passwd) != 0   ){
        ui->login_notice->setText("密码错误!");
        widgetShake(this,5);
    }else {
        if (QString::compare(username,sql.get_admin_name()) == 0){
            start->setAdmin(true);
        }
        start->set_user(username);
        start->open_mainwindow();
        start->close_welcom();
        close();
    }
}


void Login::on_iforget_linkHovered(const QString &link)
{
    ui->iforget->setText("我也没办法！");

}

void Login::on_iforget_linkActivated(const QString &link)
{
     ui->iforget->setText("我也没办法！");
}
