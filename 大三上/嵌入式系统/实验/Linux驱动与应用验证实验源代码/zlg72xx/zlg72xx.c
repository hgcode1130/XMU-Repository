//------------------------------------小键盘/数码管应用程序--------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/types.h>

#define SET_VAL _IO('Z', 0)
#define GET_KEY _IO('Z', 1)

int main(int argc, const char *argv[])
{
	int fd;
	int key = 0;
	int i = 0;
	int j;
	char value ;
	char buf[8] = {0};

	fd = open("/dev/zlg72xx", O_RDWR);
	if (fd < 0) 
	{
		perror("open");
		exit(1);
	}

	ioctl(fd, SET_VAL, buf);		//8个数码管全灭

	while(1) 
	{
		sleep(1);

		ioctl(fd, GET_KEY, &key);	//获取按键值key

		switch(key)		//将按键值转换为按键字符
		{
			case 28 : 
				printf("put is '1'\n"); 
				value = '1'; 
				break;
			case 27 : 
				printf("put is '2'\n"); 
				value = '2'; 
				break;
			case 26 : 
				printf("put is '3'\n"); 
				value = '3'; 
				break;
			case 25 : 
				printf("put is 'A'\n"); 
				value = 'A'; 
				break;
			case 20 : 
				printf("put is '4'\n"); 
				value = '4'; 
				break;
			case 19 : 
				printf("put is '5'\n"); 
				value = '5'; 
				break;
			case 18 : 
				printf("put is '6'\n"); 
				value = '6'; 
				break;
			case 17 : 
				printf("put is 'B'\n"); 
				value = 'B'; 
				break;
			case 12 : 
				printf("put is '7'\n"); 
				value = '7'; 
				break;
			case 11 : 
				printf("put is '8'\n"); 
				value = '8'; 
				break;
			case 10 : 
				printf("put is '9'\n"); 
				value = '9'; 
				break;
			case 9 : 
				printf("put is 'C'\n");  
				value = 'C'; 
				break;
			case 4 : 
				printf("put is '*'\n");  
				value = '*'; 
				break;
			case 3 : 
				printf("put is '0'\n");  
				value = '0'; 
				break;
			case 2 : 
				printf("put is '#'\n"); 
				value = '#'; 
				break;
			case 1 : 
				printf("put is 'D'\n");  
				value = 'D'; 
				break;
			default: 
				value = 0x00; 
				break;
		}

		if (value == '*' || value == '#') 	//按“*”或者“#”键，则8个数码管全灭
		{
			for (j = 0; j < 8; j++)
				buf[j] = ' ';
			i = -1;
		}
		else
		{
			for (j = 1; j < 8; j++)
				buf[j - 1] = buf[j];
			buf[7] = value;
		}
		i++;

		ioctl(fd, SET_VAL, buf);		//在数码管上显示按键值
	}
	return 0;
}

