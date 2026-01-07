//------------------------------------步进电机（位于底板上）应用程序--------------------------
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define STEPPER_ON 	0 
#define STEPPER_OFF 	1 

#if 0
#define IOCTL_MAGIC 	'S'
#define STEPPER_ON 	_IOW(IOCTL_MAGIC, 0, int) 
#define STEPPER_OFF 	_IOW(IOCTL_MAGIC, 1, int) 
#endif

#define LINES 4

char *brief[LINES] = {
	"-----------------------------",
	"|        stepper test         |",
	"| please switch D8D9D10D11    |",
	"-----------------------------",
};

void draw_string(char *buf[], unsigned int line)
{
	int i;
	for (i = 0; i < line; i++)
		printf("%s\n", buf[i]);
}

int main(int argc, const char *argv[])
{
	int fd = -1;
	int times = 900;

	draw_string(brief, LINES);

	fd = open("/dev/stepper", O_RDWR);
	if (fd < 0) 
	{
		perror("open");
		return -1;
	}

	printf("stepper test\n");

	ioctl(fd, STEPPER_OFF, 0);
	ioctl(fd, STEPPER_OFF, 1);
	ioctl(fd, STEPPER_OFF, 2);
	ioctl(fd, STEPPER_OFF, 3);

/********************************************************************
	while (1) 			//顺时针转
	{				
		ioctl(fd, STEPPER_ON, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);

		ioctl(fd, STEPPER_ON, 0);
		ioctl(fd, STEPPER_ON, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_ON, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_ON, 1);
		ioctl(fd, STEPPER_ON, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);

		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_ON, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);
	
		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_ON, 2);
		ioctl(fd, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_ON, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_ON, 3);
		usleep(times);
	}


	ioctl(fd, STEPPER_OFF, 0);
	ioctl(fd, STEPPER_OFF, 1);
	ioctl(fd, STEPPER_OFF, 2);
	ioctl(fd, STEPPER_OFF, 3);

*************************************************************************/

	while (1) 			//逆时针转
	{			
		ioctl(fd, STEPPER_ON, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_ON, 3);
		usleep(times);

		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_ON, 2);
		ioctl(fd, STEPPER_ON, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_ON, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);

		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_ON, 1);
		ioctl(fd, STEPPER_ON, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);
	
		ioctl(fd, STEPPER_OFF, 0);
		ioctl(fd, STEPPER_ON, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_ON, 0);
		ioctl(fd, STEPPER_ON, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);
		
		ioctl(fd, STEPPER_ON, 0);
		ioctl(fd, STEPPER_OFF, 1);
		ioctl(fd, STEPPER_OFF, 2);
		ioctl(fd, STEPPER_OFF, 3);
		usleep(times);
	}

	close(fd);
	return 0;
}
