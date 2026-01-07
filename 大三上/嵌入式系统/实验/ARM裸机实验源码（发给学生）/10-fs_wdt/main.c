#include "fs3399_uart.h"
#include "fs3399_wdt.h"
#include "fs3399_timer.h"
#include "fs3399_printf.h"

//看门狗
int main()
{
	int count = 10;

	//初始化串口
	fs_uart_init(115200);

	//初始化看门狗
	wdt_init();

	while (1)
	{
		count = 10;

		for (count = 10; count >= 0; count--) {
			fs_delay_s(1);

			printf("count down : %d\n\r",count);

			if (0 == count) {
				printf("feed the dog\n\r");

				WDT0->WDT_CRR = 0x76;	//喂狗
			}
		}
	};

	return 0;
}

