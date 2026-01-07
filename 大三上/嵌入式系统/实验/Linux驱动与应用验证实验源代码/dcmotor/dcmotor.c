//------------------------------------直流电机（位于底板上）应用程序--------------------------
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC 	'D'
#define DC_MOTOR_ON 	_IO(IOCTL_MAGIC, 0) 
#define DC_MOTOR_OFF 	_IO(IOCTL_MAGIC, 1) 
#define DC_MOTOR_DIR	_IOW(IOCTL_MAGIC, 2, int)	
#define DC_MOTOR_RATE	_IOW(IOCTL_MAGIC, 3, int)

#define LINES 4

char *brief[LINES] = {
	"-----------------------------",
	"|      dc_motor test        |",
	"|  please switch D12D13     |",
	"-----------------------------",
};

void draw_string(char *buf[], unsigned int line)
{
	int i;
	for (i = 0; i < line; i++)
		printf("%s\n", buf[i]);
}

int main(int argc, char **argv)
{
	int fd;
	int i = 0;

	draw_string(brief, LINES);

	fd = open("/dev/dc_motor", O_RDWR);
	if (fd < 0) 
	{
		perror("open");
		exit(1);
	}

	while(1)
	{
		printf("input your operation: 0:reverse, 1:foreward, 2:stop\n");
		scanf("%d", &i);
		getchar();

		switch(i) 
		{
		        case 0:				//逆时针转			
			ioctl(fd, DC_MOTOR_ON);
			ioctl(fd, DC_MOTOR_DIR, &i);	
			printf("foreward\n");
			break;
		        case 1:				//顺时针转
			ioctl(fd, DC_MOTOR_ON);
			ioctl(fd, DC_MOTOR_DIR, &i);
			printf("reverse\n");
			break;
		        case 2:				//停转
			ioctl(fd, DC_MOTOR_OFF);
			printf("stop\n");
		}
	}

	return 0;
}
