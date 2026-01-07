#ifndef __FS3399_ADC_H__
#define __FS3399_ADC_H__

#define CRU_BASE		0xFF760000
#define SARADC_BASE	0xFF100000

typedef volatile struct {
	unsigned int SARADC_DATA;		//contains the data after A/D Conversion
	unsigned int SARADC_STAS;		//status register of A/D Converter
	unsigned int SARADC_CTRL;		//control register of A/D Converter
	unsigned int SARADC_DLY_PU_SOC;	//delay between power up and start command 
} saradc_reg;

#define CRU_CLKGATE_CON22	(*((volatile unsigned int *)(CRU_BASE+0x0358)))
#define SARADC_REG		((saradc_reg*)SARADC_BASE)
unsigned int fs_saradc_init();

#endif
