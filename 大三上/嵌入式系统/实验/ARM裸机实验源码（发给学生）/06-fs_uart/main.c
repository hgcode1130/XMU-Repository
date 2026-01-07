#include "fs3399_uart.h"
#include "fs3399_printf.h"

int main()
{
	char str1[] = "FS3399 UART test string !";
	char str2[] = "Xiamen University";

	fs_uart_init(115200);		//串口初始化，115200 is baud rate

	//测试串口发送数据

	//发送字符
	fs_putc('A');
	fs_putc('B');
	fs_putc('C');
	fs_putc('1');
	fs_putc('2');
	fs_putc('3');
	fs_putc('a');
	fs_putc('b');
	fs_putc('c');

	fs_putc('\n');
	fs_putc('\r');

	//发送字符串
	fs_puts(str1);

	//发送字符
	fs_putc('\n');
	fs_putc('\r');

	//发送字符串
	fs_puts(str2);

	//printf函数测试
	printf("\n\r");
	printf("fs3399 test printf function\n\r");

	while (1)
	{}

	return 0;
}
