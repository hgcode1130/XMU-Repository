#include "fs3399_gpio.h"
#include "fs3399_timer.h"

//按键轮询检测：key1->led1   key2->led2
int main()
{
	//灯的状态标志位
	int led1_flag = 1;
	int led2_flag = 1;

	//设置GPIO1_B2(key1) 、GPIO0_B3(key2) 为输入模式（2个按键）
	GPIO1->SWPORTA_DDR |= (~(0x1 << (1*8 + 2)));
	GPIO0->SWPORTA_DDR |= (~(0x1 << (1*8 + 3)));
	
	//设置GPIO4_C6(LED1) 、GPIO0_A2(LED2)输出模式（2个LED灯）
	GPIO4->SWPORTA_DDR |= (0x1 << (2*8 + 6));	
	GPIO0->SWPORTA_DDR |= (0x1 << 2);

	while(1)
	{
		//轮询检测KEY1状态
		if (0 == (GPIO1->EXT_PORTA & (0x1 << (1*8 + 2)))) 			//判断  GPIO1_B2     KEY1  是否按下？
		{
			fs_delay_ms(100);	//软件消抖

			//确定key1确实按下
			if (0 == (GPIO1->EXT_PORTA & (0x1 << (1*8 + 2)))) {		//判断  GPIO1_B2     KEY1  是否按下？
				if (1 == led1_flag) {
					GPIO4->SWPORTA_DR |= (0x1 << (2*8 + 6));		//GPIO4_C6     LED1 亮
					led1_flag = 0;
				} else {
					GPIO4->SWPORTA_DR &= (~(0x1 << (2*8 + 6)));	//GPIO4_C6     LED1 灭
					led1_flag = 1;
				}
			}
		}

		//轮询检测KEY2状态
		if (0 == (GPIO0->EXT_PORTA & (0x1 << (1*8 + 3)))) 			//判断  GPIO0_B3     KEY2  是否按下？
		{
			fs_delay_ms(100);		//软件消抖

			//确定key2确实按下
			if (0 == (GPIO0->EXT_PORTA & (0x1 << (1*8 + 3)))) {		//判断  GPIO0_B3     KEY2  是否按下？
				if (1 == led2_flag) {
					GPIO0->SWPORTA_DR |= (0x1 << 2);			//GPIO0_A2     LED2 亮
					led2_flag = 0;
				} else {
					GPIO0->SWPORTA_DR &= (~(0x1 << 2));		//GPIO0_A2     LED2 灭
					led2_flag = 1;
				}
			}
		}	
	}
}
