QT       += core gui serialport widgets
TARGET = qt5ZLGDcmotorDevice
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        main.cpp \
        mainwindow.cpp \
        dcdevice.cpp \
        numkey.cpp

HEADERS += \
        mainwindow.h \
        dcdevice.h \
        numkey.h

RESOURCES += \
        icon.qrc
