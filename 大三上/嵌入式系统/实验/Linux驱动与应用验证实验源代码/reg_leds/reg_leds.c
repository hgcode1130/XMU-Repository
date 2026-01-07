//------------------------------------3个LED灯应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LED1_ON    _IO('L',11)
#define LED1_OFF   _IO('L',10)
#define LED2_ON    _IO('L',21)
#define LED2_OFF   _IO('L',20)
#define LED3_ON    _IO('L',31)
#define LED3_OFF   _IO('L',30) 

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2) 
    {
	printf("Error Usage:<%s><path>\n",argv[0]);
	return -1;
    }

    fd = open(argv[1], O_WRONLY);
    if(fd < 0)
    {
        	perror("Open file error, Check your path\n");
        	return -1;      
    }

/**************************    
    while(1)		//3个灯同时亮灭
    {
	ioctl(fd,LED1_ON);
	ioctl(fd,LED2_ON);
	ioctl(fd,LED3_ON);
	sleep(1);

	ioctl(fd,LED1_OFF);
	ioctl(fd,LED2_OFF);
	ioctl(fd,LED3_OFF);
	sleep(1);
    }
******************************/

    while(1)		//3个灯轮流亮灭
    {
	ioctl(fd,LED1_ON);
	sleep(1);
	ioctl(fd,LED1_OFF);

	ioctl(fd,LED2_ON);
	sleep(1);
	ioctl(fd,LED2_OFF);

	ioctl(fd,LED3_ON);
	sleep(1);
	ioctl(fd,LED3_OFF);
    }

    close(fd);	
    return 0;
}

