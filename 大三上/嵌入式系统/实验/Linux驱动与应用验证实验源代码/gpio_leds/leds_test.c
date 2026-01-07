//------------------------------------3个LED灯应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LED1_ON    _IO('G',1)
#define LED1_OFF   _IO('G',2)
#define LED2_ON    _IO('G',3)
#define LED2_OFF   _IO('G',4)
#define LED3_ON    _IO('G',5)
#define LED3_OFF   _IO('G',6) 

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

/***********************************  
    while(1)
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
*********************************/

    while(1)
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

