//------------------------------------ADC应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MQ3   	_IO('A',0)		//酒精
#define MQ5   	_IO('A',1)		//气体
#define FLAME	_IO('A',2)		//火焰
#define LDR   	_IO('A',3)		//光强
#define RP    	_IO('A',4)		//电位器

unsigned char *buf[7] = 
{
	"********ADC test********",
	"*       0 - 酒精       *",
 	"*       1 - 气体       *",
	"*       2 - 火焰       *",
	"*       3 - 光强       *",
 	"*       4 - 电位器     *",
 	"************************"
};

int main(int argc, char *argv[])
{
    int fd = 0;
    int ret = 0;
    unsigned int get_num = 0;

    for(ret;ret<7;ret++)
	printf("%s\n",buf[ret]);

    ret = 0;

    if (argc != 3) 
    {
	printf("Error Usage:<%s><path>\n",argv[0]);
	return -1;
    }

    fd = open((argv[1]), O_WRONLY);
    if(fd < 0)
    {
        perror("Open file error, Check your path");
        return -1;       
    }  

    ret = argv[2][1]-48;

    while(1)
    {
		if(ret >= 0 && ret <= 4)
			switch(ret) 
			{
				case 0:ioctl(fd, MQ3,   &get_num);break;	//酒精传感器
				case 1:ioctl(fd, LDR,   &get_num);break;	//气体传感器
				case 2:ioctl(fd, MQ5,   &get_num);break;	//火焰传感器
				case 3:ioctl(fd, FLAME, &get_num);break;	//光强传感器
				case 4:ioctl(fd, RP,    &get_num);break;		//电位器
				default:break;	   
			}
		printf("get_num = %d\n",get_num);
		get_num = 0;
		usleep(100000);
    }

    close(fd);
    return 0;
}

