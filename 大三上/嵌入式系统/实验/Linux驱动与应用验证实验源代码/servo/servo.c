//------------------------------------陀机（位于底板上）应用程序--------------------------
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC 	'S'
#define ROTATE_0 		_IO(IOCTL_MAGIC, 0) 
#define ROTATE_30 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_60 	_IO(IOCTL_MAGIC, 2) 
#define ROTATE_90 	_IO(IOCTL_MAGIC, 3) 
#define ROTATE_120 	_IO(IOCTL_MAGIC, 4) 
#define ROTATE_150 	_IO(IOCTL_MAGIC, 5) 
#define SET_ANGLE	_IO(IOCTL_MAGIC, 6)

#define LINES 4

char *brief[LINES] = {
	"-----------------------------",
	"|        servo test         |",
	"|     please switch D6      |",
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
	int angle = 1;

	fd = open("/dev/servo", O_RDWR);
	if (fd < 0) 
	{
		perror("open");
		exit(1);
	}

	draw_string(brief, LINES);

	while(1)
	{
		printf("Please input angle:");
		scanf("%d", &angle);
		getchar();
		
		if (angle >= 0 && angle <= 180) 
		{
			ioctl(fd, SET_ANGLE, angle);			//驱动陀机转动
			printf("rotate angle: %d\n", angle);
		}
		else
			printf("invaled value, value range is 0 ~ 180\n");
	}

	return 0;
}
