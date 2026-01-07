#include "ledDvice.h"
using namespace std;

// 打开指定编号的LED灯
ledDvice::ledDvice()
{
    led_init();
}


ledDvice::~ledDvice()
{
    led_close();
}


int ledDvice::ledOn(int nr)
{
    int ret = 0;
    ret = led_on(nr);
    if(ret<0)
    {
        perror("open led failed\n");
    }
    return ret;
}


// 关闭指定编号的LED灯
int ledDvice::ledOff(int nr)
{
    int ret = 0;
    ret = led_off(nr);
    if(ret<0)
    {
        perror("close led failed\n");
    }
    return ret;
}


int ledDvice::ledClose()
{
    return led_close();
}

