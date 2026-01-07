/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_back;
    QListWidget *listWidget;
    QPushButton *pushButton_sendmessage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Noto Sans CJK SC"));
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QFont font1;
        font1.setPointSize(18);
        centralWidget->setFont(font1);
        centralWidget->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_back = new QPushButton(centralWidget);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));
        pushButton_back->setMinimumSize(QSize(50, 50));
        pushButton_back->setFont(font);
        pushButton_back->setStyleSheet(QLatin1String("background-color: transparent;\n"
"border-image: url(:/backhome.png);"));

        verticalLayout->addWidget(pushButton_back, 0, Qt::AlignLeft);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QFont font2;
        font2.setFamily(QStringLiteral("Noto Sans CJK SC"));
        font2.setPointSize(14);
        listWidget->setFont(font2);
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    border: none; /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"}\n"
"QListWidget::item {\n"
"    background-color: #ffffff;\n"
"    padding: 15px;\n"
"    border-bottom: none;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #e1f5fe;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #03a9f4;\n"
"    color: #ffffff;\n"
"    padding: 8px 16px;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #0288d1;\n"
"}\n"
"QListWidget:focus\n"
"{\n"
"    outline: 0px;\n"
"}\n"
""));

        verticalLayout->addWidget(listWidget);

        pushButton_sendmessage = new QPushButton(centralWidget);
        pushButton_sendmessage->setObjectName(QStringLiteral("pushButton_sendmessage"));
        pushButton_sendmessage->setMinimumSize(QSize(50, 50));
        QFont font3;
        font3.setFamily(QStringLiteral("Noto Sans CJK SC"));
        font3.setPointSize(12);
        pushButton_sendmessage->setFont(font3);
        pushButton_sendmessage->setStyleSheet(QLatin1String("background-color: transparent;\n"
"border-image: url(:/new.png);"));

        verticalLayout->addWidget(pushButton_sendmessage, 0, Qt::AlignRight);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_back->setText(QString());
        pushButton_sendmessage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
