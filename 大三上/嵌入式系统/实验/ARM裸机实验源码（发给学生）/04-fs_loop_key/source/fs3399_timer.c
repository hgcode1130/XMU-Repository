#include "fs3399_timer.h"

void fs_delay_us(volatile unsigned long int  us)
{
    unsigned long int count_value = 24 * us;  	//24MHz; period=(1/24000000)*1000000=1/24us

    TIMER4->CONTROL_REG &= ~(0x01 << 0);     	//set timer disable

    TIMER4->CONTROL_REG |=  (0x01 << 1);     	//set timer mode : user-define count mode

    TIMER4->CONTROL_REG &= ~(0x01 << 2);     	//set timer interrupt mask

    TIMER4->LOAD_COUNT0 = count_value & 0xFFFFFFFF;             		//load_count_low bits

    TIMER4->CONTROL_REG |=  (0x01 << 0);     	//Timer enable

    while(!(TIMER4->INTSTATUS & (0x01 << 0)));

    TIMER4->INTSTATUS |= (0x01 << 0);        	//Write 1 clear the interrupt

    TIMER4->CONTROL_REG &= ~(0x01 << 0);     	//Timer enable disable
}

void fs_delay_ms(volatile unsigned long int ms)
{
    for(; ms > 0; ms--)
        fs_delay_us(1000);
}

void fs_delay_s(volatile unsigned long int s)
{
    for(; s > 0; s--)
        fs_delay_ms(1000);
}
