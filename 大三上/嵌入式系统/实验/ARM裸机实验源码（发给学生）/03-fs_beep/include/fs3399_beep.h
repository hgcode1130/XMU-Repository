#ifndef __FS_BEEP_H__
#define __FS_BEEP_H__

#include "fs3399_gpio.h"

#define PMUCRU_BASE		0xFF750000
#define PMUCRU_CLKGATE_CON1		(*((volatile unsigned int *)(PMUCRU_BASE+0x0104)))

int FsBeepInit(void);
int FsBeepOn(void);
int FsBeepOff(void);

#endif
