package com.farsight.buzzer;

public class Buzzer 
{
    static 
    {
        System.loadLibrary("buzzer");
    }
    public native int open();
    public native int close();
    public native int BuzzerOn();
    public native int BuzzerOff();
}
