//------------------------------------红外遥控器应用程序--------------------------
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include <poll.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include <sys/select.h>
#include <sys/time.h>

static struct input_event inputevent;

#define LINES 4

char *brief[LINES] = {
	"----------------------------------",
	"|             IR test            |",
	"|  please  press remote control  |",
	"----------------------------------",
};

void draw_string(char *buf[], unsigned int line)
{
	int i;
	for (i = 0; i < line; i++)
		printf("%s\n", buf[i]);
}

int main(int argc,char* argv[])
{
	int fd;
	int err=0;
//	char path[128] = {0};

	if (argc != 2) 
	{
		printf("Error Usage:<%s><path>",argv[0]);
		return -1;
	}
	
	draw_string(brief, LINES);
	
	fd=open(argv[1],O_RDWR);
	if (fd < 0) 
	{
		perror("Open file error, Check your path ");
		return -1;
	}

	while(1)
	{
		err=read(fd,&inputevent,sizeof(inputevent));		//获取红外遥控器按键值

		if(inputevent.value)
		{
			switch(inputevent.code)
			{
				case 0x74:printf("开关 is set\n");break;
				case 0x72:printf("音量减 is set\n");break;
				case 0x73:printf("音量加 is set\n");break;
				case 0x8d:printf("设置 is set\n");break;
				case 0x8b:printf("菜单 is set\n");break;
				case 0x67:printf("up is set\n");break;
				case 0x6c:printf("down is set\n");break;
				case 0x69:printf("left is set\n");break;
				case 0x6a:printf("right is set\n");break;
				case 0x1c:printf("ok is set\n");break;
				case 0x66:printf("主页 is set\n");break;
				case 0x01:printf("返回 is set\n");break;
				case 0x02:printf("1 is set\n");break;
				case 0x03:printf("2 is set\n");break;
				case 0x04:printf("3 is set\n");break;
				case 0x05:printf("4 is set\n");break;
				case 0x06:printf("5 is set\n");break;
				case 0x07:printf("6 is set\n");break;
				case 0x08:printf("7 is set\n");break;
				case 0x09:printf("8 is set\n");break;
				case 0x0a:printf("9 is set\n");break;
				case 0x0b:printf("0 is set\n");break;
				default:break;		 
			}
		}
	}
	return 0;
}

