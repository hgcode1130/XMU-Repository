#include "fs3399_pwm.h"

//初始化 pwm1
void FsPwm_1_Init()
{
    //设置GPIO4_C6（LED1灯）为第二功能：PWM1
    GRF_GPIO4C_IOMUX = (0x3 << 28) | (0x1 << 12);

    //先关掉PWM1输出
    PWM1->CTRL &= (~(0x1 << 0));        

    //设置时钟源，分频因子，预分频
    PWM1->CTRL |= (0x1 << 9);           		//set clock source
    PWM1->CTRL |= (0x1 << 12);          		//set pre-frequency division: 2 frequency divi
    PWM1->CTRL |= (0x1 << 16);          		//scale factor :2*512 = 1024

    //设置PWM的模式，输出波形起始极性，对齐方式
    PWM1->CTRL |= (0x1 << 1);           		//Continuous mode. PWM produces the waveform c
    PWM1->CTRL |= (0x1 << 3);           		//set Duty Cycle Output Polarity: positive
    PWM1->CTRL &= (~(0x1 << 5));        	//PWM Output mode: left aligned mode
}

//设置占空比
void FsSetDuty(unsigned int duty_val)
{
    //矫正输入的值
    if (duty_val > 1000) {
        duty_val = 1000;
    }   
    
    PWM1->PERIOD_HPR = 1000;
    PWM1->DUTY_LPR = duty_val;
}

//使能PWM
void FsEnable()
{
    PWM1->CTRL |= (0x1 << 0);
}

