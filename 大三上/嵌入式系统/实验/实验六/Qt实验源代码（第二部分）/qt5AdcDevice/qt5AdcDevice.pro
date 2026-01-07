QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#本程序适配平台以及所需宏如下：MP1A(PLAT_MP1A) MP1C(PLAT_MP1C) S5P6818(PLAT_S5P6818)
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adcdevice.cpp \
    circularprogressbar.cpp \
    main.cpp \
    mainwindow.cpp \
    hal_fs3399_adc.c \
    lis3dhdevice.cpp


HEADERS += \
    adcdevice.h \
    circularprogressbar.h \
    mainwindow.h \
    hal_fs3399_adc.h \
    lis3dhdevice.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icon.qrc
