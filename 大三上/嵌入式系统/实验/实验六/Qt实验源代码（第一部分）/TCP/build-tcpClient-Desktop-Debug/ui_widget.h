/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *messageLabel;
    QPushButton *pushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *host;
    QLineEdit *hostLineEdit;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *port;
    QLineEdit *portLineEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 600);
        messageLabel = new QLabel(Widget);
        messageLabel->setObjectName(QStringLiteral("messageLabel"));
        messageLabel->setGeometry(QRect(130, 350, 81, 31));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(460, 390, 89, 25));
        widget = new QWidget(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(130, 230, 231, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        host = new QLabel(widget);
        host->setObjectName(QStringLiteral("host"));

        horizontalLayout->addWidget(host);

        hostLineEdit = new QLineEdit(widget);
        hostLineEdit->setObjectName(QStringLiteral("hostLineEdit"));

        horizontalLayout->addWidget(hostLineEdit);

        horizontalLayout->setStretch(0, 1);
        widget1 = new QWidget(Widget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(130, 290, 231, 27));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        port = new QLabel(widget1);
        port->setObjectName(QStringLiteral("port"));

        horizontalLayout_2->addWidget(port);

        portLineEdit = new QLineEdit(widget1);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));

        horizontalLayout_2->addWidget(portLineEdit);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        messageLabel->setText(QApplication::translate("Widget", "\346\224\266\345\210\260\347\232\204\344\277\241\346\201\257", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "\346\216\245\346\224\266", Q_NULLPTR));
        host->setText(QApplication::translate("Widget", "\344\270\273\346\234\272:", Q_NULLPTR));
        port->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
