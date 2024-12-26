#include <QtDebug>
#include <QMessageBox>

#include "mymap.h"
#include "sigin.h"
#include "ui_sigin.h"
#include "base.h"
#include "mysql.h"
#include "main.h"
#include "welcom.h"

Sigin::Sigin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sigin)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
    ui->sigin_confirm->setEnabled(false);
    ui->passwd_input->setEchoMode(QLineEdit::Password);
    ui->confirm_passwd_input->setEchoMode(QLineEdit::Password);
}

Sigin::~Sigin()
{
    delete ui;
}


/**
 * @brief Sigin::on_checkBox_stateChanged
 * @param arg1
 * 当复选框 取消勾选，确认键变灰无法触发
 */
void Sigin::on_checkBox_stateChanged(int arg1)
{
    if (arg1){
        ui->sigin_confirm->setEnabled(true);
    }else {
        ui->sigin_confirm->setEnabled(false);
    }
}

/**
 * @brief Sigin::on_sigin_confirm_clicked
 *确认按钮，注册
 */
void Sigin::on_sigin_confirm_clicked()
{
    QString username = ui->username_input->text();
    QString passwd = ui->passwd_input->text();
    QString confirm_passwd = ui->confirm_passwd_input->text();
    qDebug() << "username:" << username;
    qDebug() << "passwd:" <<passwd;
    qDebug() << "confirm_passwd:" <<confirm_passwd;
    if (!username.length()){
        ui->sigin_notice->setText("");
        widgetShake(this,5);
        qDebug() << "请输入用户名！";
        return;
    }else if(passwd.length() == 0){
        ui->sigin_notice->setText("请输入密码!");
        widgetShake(this,5);
        return;
    }else if (username.length() > 20){
        ui->sigin_notice->setText("用户名过长！");
        widgetShake(this,5);
        qDebug() << "用户名过长！";
        return;
    }else if (QString::compare(passwd,confirm_passwd) != 0) {
        ui->sigin_notice->setText("两次输入密码不相同!");
        widgetShake(this,5);
        qDebug() << "两次密码不同！";
        return;
    }else if (passwd.length()  > 16) {
        ui->sigin_notice->setText("密码长度过长，16位以内");
        widgetShake(this,5);
        qDebug() << "密码长度过长";
        return;
    }

    if (!check_string(username) || !check_string(passwd)){
        qDebug() << "非法输入!";
        ui->sigin_notice->setText("请输入字母、数字或下划线以内字符！");
        widgetShake(this,5);
        return;
    }

    MySQL &sql = MySQL::getInstance() ;
    if (sql.add_user(username,passwd,"0")){
        QMessageBox::about(this,"成功","注册成功，正在以：" + username + " 身份登录...");
        start->set_user(username);
        start->close_welcom();
        start->open_mainwindow();
        close();
        return;
    }
    QMessageBox::about(this,"失败","啊哦，出问题了！");
}

/**
 * @brief Sigin::on_sigin_cancel_clicked
 *取消 关闭窗口
 */
void Sigin::on_sigin_cancel_clicked()
{
    close();
}
