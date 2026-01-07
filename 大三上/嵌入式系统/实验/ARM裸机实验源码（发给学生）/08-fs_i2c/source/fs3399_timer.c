#include "fs3399_timer.h"
#include "fs3399_gpio.h"

void fs_delay_us(volatile unsigned long int  us)
{
    unsigned long int count_value = 24 * us;  	//clk=24MHz; period=(1/24000000)*1000000=1/24us
    TIMER4->CONTROL_REG &= ~(0x01 << 0);     	//先关掉timer
    TIMER4->CONTROL_REG |=  (0x01 << 1);     	//设置模式 : user-define count mode
    TIMER4->CONTROL_REG &= ~(0x01 << 2);     	//中断屏蔽(不需要中断处理函数)
    TIMER4->LOAD_COUNT0 = count_value & 0xFFFFFFFF;             		//设置计数值，低32位
    TIMER4->CONTROL_REG |=  (0x01 << 0);     	//使能timer
    while(!(TIMER4->INTSTATUS & (0x01 << 0)));	//轮询的方式去中断状态位判断
    TIMER4->INTSTATUS |= (0x01 << 0);        	//若产生中断，清除中断位
    TIMER4->CONTROL_REG &= ~(0x01 << 0);     	//关闭timer
}

void fs_delay_ms(volatile unsigned long int ms)
{
    for(; ms > 0; ms--)
        fs_delay_us(1000);		//ms * 1000us
}

void fs_delay_s(volatile unsigned long int s)
{
    for(; s > 0; s--)
        fs_delay_ms(1000);		//s * 1000ms
}
