#include "keydevice.h"

KeyDevice::KeyDevice()
{
    key_init();
}

void KeyDevice::getKeys()
{
    while(1){
        int ret = get_keys_clicked();
        if(ret < 0)
        {
            qDebug()<<"get Keys faile";
        }
        emit KeysState(ret);
    }
}

KeyDevice::~KeyDevice()
{
    key_close();
}


