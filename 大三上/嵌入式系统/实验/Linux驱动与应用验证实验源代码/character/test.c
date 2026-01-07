//------------------------------------字符设备应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
    	int fd;
    	int i;
	int ret;
	char buf[20];

	if (argc != 2) 
	{
		printf("Error Usage:<%s><path>\n",argv[0]);
		return -1;
	}

    	fd = open(argv[1], O_RDWR);		//打开设备文件
    	if(fd < 0)
    	{
        		perror("Open file error, Check your path");
        		return -1;      
    	}
	printf("open success\n");

	ret = write(fd,"APP test",8);		//写操作
	if(ret == 8 )
		printf("write success\n");
	
	ret = read(fd, buf, 5);		//读操作
	printf("read success : ");
	for(i=0;i<ret;i++)
		printf("%c ",buf[i]);
	printf("\n");
	memset(buf,0,sizeof(buf));
		
    	ret = ioctl(fd,'a',0);			//ioctl 操作
    	ret = ioctl(fd,'b',0);
	printf("ioctl success\n");

    	close(fd);				//关闭设备文件
    
    	return 0;
}

