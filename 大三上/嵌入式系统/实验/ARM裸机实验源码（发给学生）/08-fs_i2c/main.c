#include "fs3399_uart.h"
#include "fs3399_timer.h"
#include "fs3399_I2C.h"
#include "fs3399_printf.h"

int main()
{
	unsigned short val = 0;
	unsigned short temp_h = 0;
	unsigned short temp_l = 0;
	unsigned short  temp = 0;

	fs_uart_init(115200);		//串口初始化
	i2c_init();				//I2C初始化

	while (1) {
		val = temp_read(0x00);			//读取温度原始值

		temp_h = val & 0xff;			//调换原始值的高8位 和低8位
		temp_l = (val >> 8) & 0xff;
		temp = (temp_h << 8 | temp_l) >> 5;		//去掉无效的低5位

		printf("temp_val = %d.%d\n\r",temp*125/1000, temp*125%1000);

		fs_delay_ms(2000);
	}

	return 0;
}
