//------------------------------------呼吸灯（PWM）应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LED1_PERIOD    _IO('L',0)
#define LED1_DUTY      _IO('L',1)
#define LED1_ON        _IO('L',2)
#define LED1_OFF       _IO('L',3)

int main(int argc, char *argv[])
{
    int fd;
    unsigned int i;
    unsigned int per;

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
  
    printf("LED ON\n");
    ioctl(fd,LED1_ON);

/************************************************************
    per = 100;
    ioctl(fd,LED1_PERIOD, &per);
    while(1)		//呼吸灯的时间长
    {
		//控制LED亮灭
		for(i=0;i<=100;i++)
		{
			ioctl(fd,LED1_DUTY, &i);
			usleep(30000);
		}
		for(i=100;i>0;i--)
		{
			ioctl(fd,LED1_DUTY,&i);
			usleep(30000);
		}
    }
*************************************************************/

    per = 50;
    ioctl(fd,LED1_PERIOD, &per);
    while(1)		//呼吸灯的时间短
    {
		//控制LED亮灭
		for(i=0;i<=50;i++)
		{
			ioctl(fd,LED1_DUTY, &i);
			usleep(30000);
		}
		for(i=50;i>0;i--)
		{
			ioctl(fd,LED1_DUTY,&i);
			usleep(30000);
		}
    }

    ioctl(fd,LED1_OFF);
    close(fd);
    return 0;
}

