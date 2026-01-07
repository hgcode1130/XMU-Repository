QT       += core gui
TARGET = qt5ZLGAdcDevice
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        main.cpp \
        mainwindow.cpp \
        adcdevice.cpp \
        displayandmatrix.cpp \
        hal_fs3399_adc.c \
        hal_fs3399_displayandmatrix.c

HEADERS += \
        mainwindow.h \
        adcdevice.h \
        displayandmatrix.h \
        hal_fs3399_adc.h \
        hal_fs3399_displayandmatrix.h


