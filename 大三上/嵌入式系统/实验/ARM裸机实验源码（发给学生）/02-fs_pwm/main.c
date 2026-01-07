#include "fs3399_pwm.h"
#include "fs3399_timer.h"

/*-------------呼吸灯程序--------------------------*/

int main()
{
	unsigned int i = 0;

	//pwm初始化
	FsPwm_1_Init();

	//使能pwm
	FsEnable();

	//通过循环的方式。不断改变PWM脉冲的占空比，实现呼吸灯
	for (;;) 
	{
		for (i = 0; i <= 1000; i++) 
		{
			FsSetDuty(i);
			fs_delay_ms(1);
		}

		for (i = 1000; i > 0; i--) 
		{
			FsSetDuty(i);
			fs_delay_ms(1);
		}
	}

	return 0;
}
