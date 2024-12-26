/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *login_passwd;
    QPushButton *login_confirm;
    QPushButton *login_cancel;
    QLabel *iforget;
    QLineEdit *login_username;
    QLabel *login_notice;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(441, 301);
        Login->setMinimumSize(QSize(441, 301));
        Login->setMaximumSize(QSize(441, 301));
        groupBox = new QGroupBox(Login);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 50, 321, 201));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 20, 271, 161));
        widget->setMinimumSize(QSize(0, 121));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 54, 12));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 61, 31));
        login_passwd = new QLineEdit(widget);
        login_passwd->setObjectName("login_passwd");
        login_passwd->setGeometry(QRect(60, 70, 121, 20));
        login_confirm = new QPushButton(widget);
        login_confirm->setObjectName("login_confirm");
        login_confirm->setGeometry(QRect(20, 120, 75, 23));
        login_cancel = new QPushButton(widget);
        login_cancel->setObjectName("login_cancel");
        login_cancel->setGeometry(QRect(150, 120, 75, 23));
        iforget = new QLabel(widget);
        iforget->setObjectName("iforget");
        iforget->setGeometry(QRect(190, 70, 71, 31));
        login_username = new QLineEdit(widget);
        login_username->setObjectName("login_username");
        login_username->setGeometry(QRect(60, 20, 121, 21));
        login_notice = new QLabel(groupBox);
        login_notice->setObjectName("login_notice");
        login_notice->setGeometry(QRect(90, 10, 171, 20));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "\345\257\206  \347\240\201\357\274\232", nullptr));
        login_confirm->setText(QCoreApplication::translate("Login", "\347\241\256\350\256\244", nullptr));
        login_cancel->setText(QCoreApplication::translate("Login", "\345\217\226\346\266\210", nullptr));
#if QT_CONFIG(tooltip)
        iforget->setToolTip(QCoreApplication::translate("Login", "<html><head/><body><p>\351\207\215\346\226\260\346\263\250\345\206\214\347\275\242\357\274\214\346\210\221\345\217\210\344\270\215\347\237\245\351\201\223\344\275\240\347\232\204\345\257\206\347\240\201\357\274\201</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        iforget->setText(QCoreApplication::translate("Login", "<html><head/><body><p><span style=\" font-size:14pt; text-decoration: underline; color:#aa00ff; vertical-align:sub;\">\345\277\230\350\256\260\345\257\206\347\240\201\357\274\237</span></p></body></html>", nullptr));
        login_notice->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
