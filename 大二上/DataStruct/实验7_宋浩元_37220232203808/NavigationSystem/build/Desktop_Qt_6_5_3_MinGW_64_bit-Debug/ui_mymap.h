/********************************************************************************
** Form generated from reading UI file 'mymap.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAP_H
#define UI_MYMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyMap
{
public:
    QScrollArea *Painter;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *MyMap)
    {
        if (MyMap->objectName().isEmpty())
            MyMap->setObjectName("MyMap");
        MyMap->resize(789, 924);
        Painter = new QScrollArea(MyMap);
        Painter->setObjectName("Painter");
        Painter->setGeometry(QRect(0, 0, 791, 921));
        Painter->setStyleSheet(QString::fromUtf8("background-image: url(:/map/map/all.png);"));
        Painter->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 789, 919));
        Painter->setWidget(scrollAreaWidgetContents);

        retranslateUi(MyMap);

        QMetaObject::connectSlotsByName(MyMap);
    } // setupUi

    void retranslateUi(QWidget *MyMap)
    {
        MyMap->setWindowTitle(QCoreApplication::translate("MyMap", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyMap: public Ui_MyMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAP_H
