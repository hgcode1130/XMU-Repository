//------------------------------------CAN总线发送应用程序--------------------------
#include <stdio.h>
#include "sockcan.h"

int main(int argc, const char *argv[])
{
	int fd;
	int nbyte;
	int i;
	unsigned char data[8] = {0x61, 0x63, 0x62, 0x64};
	unsigned int can_id = 0x1234;
	unsigned int extended = 1;

	struct can_filter filter[] = {
		{0x4321,CAN_EFF_MASK,},
		{0x1234,CAN_EFF_MASK,},
	}; 

	fd = can_open("can0", 500000, filter, sizeof(filter)  / sizeof(struct can_filter));
	if (fd < 0) 
	{
		perror("can_open");
		can_close("can0", fd);
		exit(1);
	}

	while(1)
	{
		printf("canwrite data: 0x61,0x62,0x63,0x64\n");
		can_write(fd, can_id, data, sizeof(data), extended);
		sleep(1);
	}

	can_close("can0", fd);
	return 0;
}
