#include "fs3399_uart.h"
#include "fs3399_adc.h"
#include "fs3399_printf.h"
#include "fs3399_timer.h"

int main()
{
	unsigned int val = 0;
	unsigned int resolution = 175;	//0.00175*100000

	//初始化串口
	fs_uart_init(115200);

	while (1)
	{
		val = fs_saradc_init();

		printf("val = %d.%dV\n\r", (val*175)/100000, ((val*175)%100000)/100);

		fs_delay_ms(500);
	}

	return 0;
}
