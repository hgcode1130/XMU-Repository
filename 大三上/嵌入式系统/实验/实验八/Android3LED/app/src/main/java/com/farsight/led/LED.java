package com.farsight.led;

public class LED 
{
    static 
    {
        System.loadLibrary("led");
    }
    public native int open();
    public native int close();
    public native int LedOn1();
    public native int LedOff1();
    public native int LedOn2();
    public native int LedOff2();

    public native int LedOn3();

    public native int LedOff3();
}
