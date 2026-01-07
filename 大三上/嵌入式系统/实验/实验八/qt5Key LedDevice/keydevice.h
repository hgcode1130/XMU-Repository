#ifndef KEYDEVICE_H
#define KEYDEVICE_H

extern "C"
{
#include "hal_fs3399_key.h"
}

#include <QWidget>
#include <QDebug>

class KeyDevice : public QObject
{
    Q_OBJECT

public:
    KeyDevice();
    void getKeys();
    ~KeyDevice();

signals:
    void KeysState(int keyStates);
};

class ledDvice : public QWidget 	
{
    Q_OBJECT

public:
    ledDvice();
    ~ledDvice();
    int ledOn(int nr);
    int ledOff(int nr);
    int ledClose();
};

#endif
