#include "fs3399_gpio.h"
#include "fs3399_timer.h"

//利用定时器，间隔1s依次点亮3个LED灯
int main()
{
	//设置LED1对应的GPIO管脚为输出模式
	GPIO4->SWPORTA_DDR |= (0x1 << 22);	//GPIO4_C6

	//设置LED2对应的GPIO管脚为输出模式
	GPIO0->SWPORTA_DDR |= (0x1 << 2);	//GPIO0_A2

	//设置LED3对应的GPIO管脚为输出模式
	GPIO0->SWPORTA_DDR |= (0x1 << 12);	//GPIO0_B4

	while(1){
		//点亮LED1
		GPIO4->SWPORTA_DR |= (0x1 << 22);
		//delay 1S
		fs_delay_s(1);

		//点亮LED2
		GPIO0->SWPORTA_DR |= (0x1 << 2);
		//delay 1S
		fs_delay_s(1);

		//点亮LED3
		GPIO0->SWPORTA_DR |= (0x1 << 12);
		//delay 1S
		fs_delay_s(1);

		//熄灭LED1
		GPIO4->SWPORTA_DR &= ~(0x1 << 22);
		//delay 1S
		fs_delay_s(1);

		//熄灭LED2
		GPIO0->SWPORTA_DR &= ~(0x1 << 2);
		//delay 1S
		fs_delay_s(1);

		//熄灭LED3
		GPIO0->SWPORTA_DR &= ~(0x1 << 12);
		//delay 1S
		fs_delay_s(1);
	}
	
	return 0;
}
