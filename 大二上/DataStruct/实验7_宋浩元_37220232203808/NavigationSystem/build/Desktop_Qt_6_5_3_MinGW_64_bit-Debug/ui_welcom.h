/********************************************************************************
** Form generated from reading UI file 'welcom.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOM_H
#define UI_WELCOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Welcom
{
public:
    QLabel *label;
    QPushButton *login_button;
    QPushButton *sigin_buttom;
    QLabel *logo;
    QLabel *Title;

    void setupUi(QWidget *Welcom)
    {
        if (Welcom->objectName().isEmpty())
            Welcom->setObjectName("Welcom");
        Welcom->resize(750, 612);
        label = new QLabel(Welcom);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 750, 611));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/src/icon/src/img/welcome.jpg);"));
        login_button = new QPushButton(Welcom);
        login_button->setObjectName("login_button");
        login_button->setGeometry(QRect(430, 440, 141, 41));
        login_button->setStyleSheet(QString::fromUtf8("\n"
"font: 75 14pt \"Segoe Print\";\n"
"background-color: rgba(255, 85, 255,0.5);"));
        sigin_buttom = new QPushButton(Welcom);
        sigin_buttom->setObjectName("sigin_buttom");
        sigin_buttom->setGeometry(QRect(170, 440, 151, 41));
        sigin_buttom->setStyleSheet(QString::fromUtf8("\n"
"font: 75 14pt \"Segoe Print\";\n"
"background-color: rgba(255, 85, 255,0.5);"));
        logo = new QLabel(Welcom);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(0, -30, 241, 121));
        logo->setStyleSheet(QString::fromUtf8("image: url(:/src/icon/logo);"));
        Title = new QLabel(Welcom);
        Title->setObjectName("Title");
        Title->setGeometry(QRect(0, 170, 651, 111));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font.setPointSize(36);
        Title->setFont(font);
        Title->setAlignment(Qt::AlignCenter);

        retranslateUi(Welcom);

        QMetaObject::connectSlotsByName(Welcom);
    } // setupUi

    void retranslateUi(QWidget *Welcom)
    {
        Welcom->setWindowTitle(QCoreApplication::translate("Welcom", "Form", nullptr));
        label->setText(QString());
        login_button->setText(QCoreApplication::translate("Welcom", "\347\231\273\345\275\225", nullptr));
        sigin_buttom->setText(QCoreApplication::translate("Welcom", "\346\263\250\345\206\214", nullptr));
        logo->setText(QString());
        Title->setText(QCoreApplication::translate("Welcom", "\345\216\246\351\227\250\345\244\247\345\255\246\347\277\224\345\256\211\346\240\241\345\214\272\345\257\274\350\210\252\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Welcom: public Ui_Welcom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOM_H
