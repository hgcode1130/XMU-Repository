#include "fs3399_beep.h"

int FsBeepInit()
{
	//设置GPIO1_C7为输出模式
	GPIO1->SWPORTA_DDR |= (0x1 << 23);
	return 0;
}

int FsBeepOn()
{
	//设置GPIO1_C7 输出高电平
	GPIO1->SWPORTA_DR |= (0x1 << 23);
	return 0;
}

int FsBeepOff()
{
	//设置GPIO1_C7 输出低电平
	GPIO1->SWPORTA_DR &= (~(0x1 << 23));
	return 0;
}

