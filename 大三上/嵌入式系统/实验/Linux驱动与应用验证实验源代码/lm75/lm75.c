//------------------------------------温度传感器（位于MPU开发板上）应用程序--------------------------
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

int main (void) 
{
	int fd;
	int data;

	fd = open ("/dev/temp",O_RDWR);
	if (fd < 0) 
	{
		perror("open");
		exit(0);
	}

	printf("-----------  TEST LM75 -------------\n");

	while(1)
	{
		read (fd, (char *)&data, sizeof(data));
		sleep(1);
		printf("temperature: ");
		printf("%.3f\n", (0.125*(data>>5)));
	}

	close (fd);
	return 0;
}

