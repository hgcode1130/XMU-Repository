#-------------------------------------------------
#
# Project created by QtCreator 2023-05-25T07:16:40
#
#-------------------------------------------------

QT       += core gui
QT       += serialport network
CONFIG   += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt5msg
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS   PLAT_S5P6818

SOURCES += main.cpp\
    mainwindow.cpp \
    my_textedit.cpp \
    newsms.cpp \
    sms.cpp \
    syszuxpinyin.cpp \
    my_lineedit.cpp \
    lis3dhdevice.cpp

HEADERS  += mainwindow.h \
    my_textedit.h \
    newsms.h \
    sms.h \
    syszuxpinyin.h \
    my_lineedit.h \
    lis3dhdevice.h \
    chatlabel.h

FORMS    += mainwindow.ui \
    syszuxpinyin.ui

RESOURCES += \
    pic.qrc \
    qtr.qrc
