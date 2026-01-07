#include "fs3399_beep.h"
#include "fs3399_timer.h"

/*-----------------蜂鸣器程序---------------------*/

int main()
{
	//设置GPIO1_C7 为输出模式
	FsBeepInit();

	//打开蜂鸣器
	FsBeepOn();
	
	//延时3s
	fs_delay_s(1);

	//关闭蜂鸣器
	FsBeepOff();

	//延时3s
	fs_delay_s(1);

	//打开蜂鸣器
	FsBeepOn();

	//延时3s
	fs_delay_s(1);

	//关闭蜂鸣器
	FsBeepOff();

	//延时3s
	fs_delay_s(1);

	//打开蜂鸣器
	FsBeepOn();

	//延时3s
	fs_delay_s(1);

	//关闭蜂鸣器
	FsBeepOff();

	//延时3s
	fs_delay_s(1);

	return 0;
}
