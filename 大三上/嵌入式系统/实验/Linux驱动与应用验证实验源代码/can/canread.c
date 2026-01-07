//------------------------------------CAN总线接收应用程序--------------------------
#include <stdio.h>
#include "sockcan.h"

int main(int argc, const char *argv[])
{
	int fd;
	int nbyte;
	int i;
	unsigned char data[8] = {0};
	unsigned int can_id = 0;
	unsigned int extended = 0;
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
		nbyte = can_read(fd, &can_id, data, &extended);
		printf("canid = %x, len = %d data = ", can_id, nbyte);
		for(i = 0; i < nbyte; i++) 
		{
			printf("%02x ", data[i]);	
		}
		printf("\n");
	}

	can_close("can0", fd);

	return 0;
}
