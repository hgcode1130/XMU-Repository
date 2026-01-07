#ifndef __FS_LED_H__
#define __FS_LED_H__

#include "fs3399_gpio.h"

#define PMUCRU_BASE 0xFF750000

//pclk_gpio1_en
//#define PMUCRU_CLKGATE_CON1 (*((volatile unsigned int *)(PMUCRU_BASE+0x0104)))

int FsLedInit(void);

int FsLedOn(int);

int FsLedOff(int);

#endif /* __FS_LED_H__ */