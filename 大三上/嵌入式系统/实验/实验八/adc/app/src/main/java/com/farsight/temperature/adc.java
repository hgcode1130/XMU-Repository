package com.farsight.temperature;

public class adc {
    static {
        System.loadLibrary("temperature"); // ���ر��ؿ�
    }

    // ��ADC�豸
    public native int open();

    // ��ȡADC����
    public native int read();

    // �ر�ADC�豸
    public native int close();
}
