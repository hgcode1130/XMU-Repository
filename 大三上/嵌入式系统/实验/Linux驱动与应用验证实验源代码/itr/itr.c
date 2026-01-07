//------------------------------------光电开关应用程序--------------------------
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
	printf("=======ITR test=======\n");

	int fd = open("/dev/rk3399_itr", O_RDWR);
	if(-1 == fd ) 
	{
		perror("open tr");
		return -1 ;
	}

	while(1)
	{
		int status;
		read(fd,&status,sizeof(status));	//读光电开关信号
		printf("status:%d\n",status);
		sleep(1);
	}

	close(fd);
}
