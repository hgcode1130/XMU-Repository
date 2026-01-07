//------------------------------------蜂鸣器（位于底板上）应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define IOCTL_MAGIC 	'B'
#define ROTATE_ON 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_OFF 	_IO(IOCTL_MAGIC, 0) 

int main(void)
{
    int fd;
    int ret;
    int get_num;

    fd = open("/dev/buzzer", O_WRONLY);
    if(fd < 0)
    {
        perror("open buzzer driver");
        return -1;      
    }
  
    while(1)
    {
		printf("please input '0' or '1' : \n");
		scanf("%d",&get_num);
		getchar();

		if(get_num == 1)
		{
       			ret = ioctl(fd,ROTATE_ON);			//蜂鸣器响
       			if(ret < 0)
           				perror("buzzer driver ");
		}

		if(get_num == 0)
		{
       			ret = ioctl(fd,ROTATE_OFF);			//蜂鸣器不响
       			if(ret < 0 )
           				perror("buzzer driver ");
		}
    }

    close(fd);
    return 0;
}

