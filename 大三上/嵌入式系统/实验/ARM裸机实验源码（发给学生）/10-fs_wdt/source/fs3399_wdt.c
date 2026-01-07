#include "fs3399_wdt.h"
#include "fs3399_printf.h"

void wdt_init()
{
	unsigned int val = 0;

	//关闭看门狗
	WDT0->WDT_CR &= (~(0x1 << 0));
	
	//设置超时周期
	WDT0->WDT_TORR &= (~(0xF << 0));
	WDT0->WDT_TORR |= (0xF << 0);

	//设置响应模式：系统复位
	WDT0->WDT_CR &= (~(0x1 << 1));
	
	val = WDT0->WDT_CCVR;
	printf("val = %d\n\r",val);

	//重启计数器
	WDT0->WDT_CRR = 0x76;

	//开启看门狗
	WDT0->WDT_CR |= (0x1 << 0);
}
