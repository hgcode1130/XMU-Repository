#include "beepdevice.h"

beepDevice::beepDevice() {
    beep_init();  // 初始化蜂鸣器
}


int beepDevice::beepOn() {
    int ret;
    ret = beep_on();  // 打开蜂鸣器
    if(ret < 0) {
        perror("open BEEP failed\n");  // 打开蜂鸣器失败处理
    }
    return ret;
}


int beepDevice::beepOff() {
    int ret;
    ret = beep_off();  // 关闭蜂鸣器
    if(ret < 0) {
        perror("open led failed\n");  // 关闭蜂鸣器失败处理
    }
    return ret;
}


beepDevice::~beepDevice() {
    beep_close();  // 关闭蜂鸣器
}
