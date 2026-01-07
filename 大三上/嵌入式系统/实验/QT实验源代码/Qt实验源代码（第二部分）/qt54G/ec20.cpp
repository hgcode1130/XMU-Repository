#include "ec20.h"

EC20::EC20()
{
   tty_usb_open();
}


int EC20::Call(char *phone_num)
{
    return gprs_option_handle(phone_num);
}

int EC20::answerCall()
{
    answer_thephone();
    return 0;
}

char* EC20::getcall()
{
    return get_callphone();
}

int EC20::handUp()
{
    return handup();
}

QString EC20::getImei()
{
    char * buf = get_imei();
    QString str(buf);
    free(buf);
    return str;
}

MyBackend::MyBackend() {
    ec20 = new EC20();
    connect(ec20,&EC20::modelLost,this,&MyBackend::sendModelLost);
}

void MyBackend::getCall() {
    while (1) {
        QString num = ec20->getcall();
        if(num == "Answer")
        {
            emit AnwerCalled();
        }
        else if(num == "nocarrier")
            {
                emit NoCarrier();
            }
        else if(num == "modellost")
        {
            emit ModelLost();
            return;
        }
        else if(num == "ERROR")
        {
           emit SimLost();
           return;
        }
        else {
                emit callnumReceived(num);
            }
        sleep(2);
    }
}

void MyBackend::sendModelLost()
{

}



