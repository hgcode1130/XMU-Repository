//------------------------------------2个按键应用程序--------------------------
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include <poll.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>
#include <sys/select.h>
#include <sys/time.h>
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"

int main(int argc,char* argv[])
{
	int fd;
	int err=0;
	int buf[2] = {0};

	if (argc != 2) 
	{
		printf("Error Usage:<%s><path>\n",argv[0]);
		return -1;
	}

	fd=open(argv[1],O_RDWR);
	if (fd < 0) 
	{
		perror("Can't open file farsight_keys,Check your path");
		return -1;
	} 

	printf("---------- KEYS TEST ---------\n");

	while(1)
	{
		err=read(fd,buf,sizeof(buf));

		if(err>0)
		{
			if(buf[0] == 1)					//buf[0] 判断是哪一个按键
			{
				if(buf[1] == 0)				//buf[1] 判断有没有键按下
					printf("KEY1 is pressed\n");		//KEY1按下
				else
					printf("KEY1 is release\n");		//KEY1释放
			}
			if(buf[0] == 2)
			{
				if(buf[1] == 0)
					printf("KEY2 is pressed\n");		//KEY2按下
				else
					printf("KEY2 is release\n");		//KEY2释放
			}	
		}
	}

	return 0;
}
