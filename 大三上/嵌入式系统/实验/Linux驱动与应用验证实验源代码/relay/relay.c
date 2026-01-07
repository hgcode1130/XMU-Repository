//------------------------------------继电器应用程序--------------------------
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define RELAY_ON 	0 
#define RELAY_OFF 	1

#define LINES 4

char *brief[LINES] = {
	"-----------------------------",
	"|        relay test         |",
	"|    please switch D16      |",
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
	int ch;

	draw_string(brief, LINES);

	fd = open("/dev/relay", O_RDWR);
	if (fd < 0) 
	{
		perror("open");
		exit(1);
	}
	
	ch = 0;

	while(1)
	{
		printf("please input: 0:off, 1:on\n");
		scanf("%d", &ch);
		getchar();

		switch(ch)
		{
			case 1:
				ioctl(fd, RELAY_ON);	//打开继电器
				break;
			case 0:
				ioctl(fd, RELAY_OFF);	//关闭继电器
				break;
			default:
				break;	
		}
	}

	return 0;
}
