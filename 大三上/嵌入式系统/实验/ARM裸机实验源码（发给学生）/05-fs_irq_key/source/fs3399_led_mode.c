#include "fs3399_led_mode.h"

void led_mode(int mode)
{
    //设置2个管脚为输出模式
    GPIO4->SWPORTA_DDR |=  (0x01 << (2 * 8 + 6));	//LED1灯
    GPIO0->SWPORTA_DDR |=  (0x01 << 2);		//LED2灯

    //2个灯全灭
    GPIO4->SWPORTA_DR  &=  ~(0x01 << (2 * 8 + 6));
    GPIO0->SWPORTA_DR  &=  ~(0x01 << 2);

    if(0 == mode)		//2个灯全灭
    {
        GPIO4->SWPORTA_DR  &=  ~(0x01 << (2 * 8 + 6));
        GPIO0->SWPORTA_DR  &=  ~(0x01 << 2);
    }
    else if(1 == mode)	//LED1灯亮
    {
        GPIO4->SWPORTA_DR  |=  (0x01 << (2 * 8 + 6));
    }
    else if(2 == mode)	//LED2灯亮
    {
        GPIO0->SWPORTA_DR  |=  (0x01 << 2);
    }
    else if(3 == mode)	//2个灯全亮
    {
        GPIO4->SWPORTA_DR  |=  (0x01 << (2 * 8 + 6));
        GPIO0->SWPORTA_DR  |=  (0x01 << 2);
    }
    else if(4 == mode)	//LED1灯灭
    {
        GPIO4->SWPORTA_DR  &=  ~(0x01 << (2 * 8 + 6));
    }
    else if(5 == mode)	//LED2灯灭
    {
        GPIO0->SWPORTA_DR  &=  ~(0x01 << 2);
    }
}








