#include "fs3399_adc.h"
#include "fs3399_timer.h"

unsigned int fs_saradc_init()
{
	unsigned int val;

	//停止ADC转换
	SARADC_REG->SARADC_CTRL &= (~(0x1 << 3));

	//禁用中断
	SARADC_REG->SARADC_CTRL &= (~(0x1 << 5));

	//ADC采集通道选择
	SARADC_REG->SARADC_CTRL &= (~(0x7 << 0));	//bic [2:0]

	SARADC_REG->SARADC_CTRL |= (0x2 << 0);		//010 : Input source 2 (SARADC_AIN[2])

	//使能ADC转换器
	SARADC_REG->SARADC_CTRL |= (0x1 << 3);

	//等待数据采集后，再去轮询
	fs_delay_us(100);

	//轮询判断 adc_status 停止位，转换停止时，读取数据
	while (((SARADC_REG->SARADC_STAS) & (0x1 << 0)) == 1);

	val = SARADC_REG->SARADC_DATA & 0x3FF;

	return val;
}

