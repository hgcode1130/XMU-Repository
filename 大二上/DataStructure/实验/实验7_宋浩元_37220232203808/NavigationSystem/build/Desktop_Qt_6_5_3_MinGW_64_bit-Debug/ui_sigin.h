/********************************************************************************
** Form generated from reading UI file 'sigin.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGIN_H
#define UI_SIGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Sigin
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *username_input;
    QLabel *label_2;
    QLineEdit *passwd_input;
    QLabel *label_3;
    QLineEdit *confirm_passwd_input;
    QLabel *sigin_notice;
    QPushButton *sigin_confirm;
    QPushButton *sigin_cancel;
    QCheckBox *checkBox;
    QLabel *label_4;

    void setupUi(QDialog *Sigin)
    {
        if (Sigin->objectName().isEmpty())
            Sigin->setObjectName("Sigin");
        Sigin->resize(471, 300);
        Sigin->setMaximumSize(QSize(471, 300));
        Sigin->setFocusPolicy(Qt::ClickFocus);
        groupBox = new QGroupBox(Sigin);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(110, 50, 241, 141));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 30, 54, 12));
        username_input = new QLineEdit(groupBox);
        username_input->setObjectName("username_input");
        username_input->setGeometry(QRect(100, 30, 113, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 70, 54, 12));
        passwd_input = new QLineEdit(groupBox);
        passwd_input->setObjectName("passwd_input");
        passwd_input->setGeometry(QRect(100, 70, 113, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 110, 54, 12));
        confirm_passwd_input = new QLineEdit(groupBox);
        confirm_passwd_input->setObjectName("confirm_passwd_input");
        confirm_passwd_input->setGeometry(QRect(100, 110, 113, 20));
        sigin_notice = new QLabel(groupBox);
        sigin_notice->setObjectName("sigin_notice");
        sigin_notice->setGeometry(QRect(80, 10, 131, 20));
        sigin_confirm = new QPushButton(Sigin);
        sigin_confirm->setObjectName("sigin_confirm");
        sigin_confirm->setGeometry(QRect(110, 230, 75, 23));
        sigin_cancel = new QPushButton(Sigin);
        sigin_cancel->setObjectName("sigin_cancel");
        sigin_cancel->setGeometry(QRect(270, 230, 75, 23));
        checkBox = new QCheckBox(Sigin);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(110, 200, 101, 16));
        checkBox->setStyleSheet(QString::fromUtf8(""));
        checkBox->setTristate(false);
        label_4 = new QLabel(Sigin);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(220, 200, 61, 16));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(85, 0, 255);\n"
"text-decoration: underline;\n"
"font: 25 9pt \"Bahnschrift Light\";"));

        retranslateUi(Sigin);

        QMetaObject::connectSlotsByName(Sigin);
    } // setupUi

    void retranslateUi(QDialog *Sigin)
    {
        Sigin->setWindowTitle(QCoreApplication::translate("Sigin", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Sigin", "\347\224\250\346\210\267\346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("Sigin", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("Sigin", "\345\257\206 \347\240\201\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Sigin", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        sigin_notice->setText(QString());
        sigin_confirm->setText(QCoreApplication::translate("Sigin", "\347\241\256\350\256\244", nullptr));
        sigin_cancel->setText(QCoreApplication::translate("Sigin", "\345\217\226\346\266\210", nullptr));
#if QT_CONFIG(whatsthis)
        checkBox->setWhatsThis(QCoreApplication::translate("Sigin", "<html><head/><body><p>\345\210\232\345\210\232i\347\273\231</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        checkBox->setText(QCoreApplication::translate("Sigin", "\346\210\221\345\267\262\351\230\205\350\257\273\345\271\266\345\220\214\346\204\217", nullptr));
#if QT_CONFIG(tooltip)
        label_4->setToolTip(QCoreApplication::translate("Sigin", "<html><head/><body><p><span style=\" font-size:11pt;\">\346\234\215\345\212\241\346\235\241\346\254\276\357\274\232</span></p><p><span style=\" font-size:11pt;\">1\343\200\201\346\210\221\350\257\264\344\272\206\347\256\227\357\274\201</span></p><p><span style=\" font-size:11pt;\">2\343\200\201\346\262\241\344\272\206</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        label_4->setWhatsThis(QCoreApplication::translate("Sigin", "<html><head/><body><p>\346\234\215\345\212\241\346\235\241\346\254\276\345\260\261\346\230\257\357\274\214\346\210\221\350\257\264\344\272\206\347\256\227\357\274\201\357\274\201\357\274\201\357\274\201</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_4->setText(QCoreApplication::translate("Sigin", "\346\234\215\345\212\241\346\235\241\346\254\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sigin: public Ui_Sigin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGIN_H
