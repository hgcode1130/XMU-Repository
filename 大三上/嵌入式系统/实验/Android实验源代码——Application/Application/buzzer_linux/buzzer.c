//------------------------------------蜂鸣器（位于MPU开发板上）应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define Buzzer_on   1
#define Buzzer_off  0

int main(int argc, char *argv[])
{
    int fd;
    int ret;
    int get_num;

    if (argc != 2) 
    {
		printf("Error Usage:<%s><path>\n",argv[0]);
		return -1;
    }

    fd = open(argv[1], O_WRONLY);
    if(fd < 0)
    {
        		perror("Open file error, Check your path");
        		return -1;      
    }
  
    while(1)
    {
		printf("please input '0' or '1' : \n");
		scanf("%d",&get_num);
		getchar();

		if(get_num == 1)
		{
       			ret = ioctl(fd,Buzzer_on);
       			if(ret < 0)
           				perror("ioctl buzzer_ctl driver ");
		}
		else if(get_num == 0)
		{
       			ret = ioctl(fd,Buzzer_off);
       			if(ret < 0 )
           				perror("ioctl buzzer driver ");
		}
		else
			printf("input err : \n");
    }

    close(fd);
    return 0;
}

