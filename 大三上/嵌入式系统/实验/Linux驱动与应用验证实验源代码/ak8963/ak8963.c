//------------------------------------三轴磁感应应用程序--------------------------
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

#define MAX 3
#define LENTH 128

char buf[MAX][LENTH] = {0};

int fd[3] = {0};
//int i = 0;

int get_value(unsigned val)
{
	unsigned char data[20];
	int err=0;
	double adc_data;

	fd[val]=open(buf[val],O_RDWR);
	if (fd[val]<0) 
	{
		perror("Can't open file in_anglvel_*_raw");
		return -1;
	}

	err=read(fd[val],data,sizeof(data));

	if(err>0)
	{
		adc_data = atoi(data);
		adc_data = adc_data * 0.006562;	
		switch(val)
		{
			case 0:	printf("x=%.2f    ",adc_data);break;
			case 1:	printf("y=%.2f    ",adc_data);break;
			case 2:	printf("z=%.2f\n",adc_data);break;
			default:	break;
		}
	}
	else
	{
		printf("读取数据失败 err = %d\r\nbuf = %s\r\n",err,buf[val]);
	}
	
	adc_data = 0;

	close(fd[val]);
	return 0;
}

int main(int argc,char* argv[])
{
	printf("/*ak8963 - test*/\n");

	snprintf(buf[0], LENTH, "/sys/bus/iio/devices/%s/in_magn_x_raw",argv[1]);
	snprintf(buf[1], LENTH, "/sys/bus/iio/devices/%s/in_magn_y_raw",argv[1]);
	snprintf(buf[2], LENTH, "/sys/bus/iio/devices/%s/in_magn_z_raw",argv[1]);
	
//	int i = 0;
	
	while(1)
	{
		get_value(0);
		get_value(1);
		get_value(2);
		usleep(500000);
	}

	return 0;
}
