#ifndef __FS3399_WDT_H__
#define __FS3399_WDT_H__

#define WDT0_BASE	0xFF848000
#define WDT1_BASE	0xFF840000

typedef volatile struct {
	unsigned int WDT_CR;		//Control Register
	unsigned int WDT_TORR;		//Timeout range Register
	unsigned int WDT_CCVR;		//Current counter value Register
	unsigned int WDT_CRR;		//Counter restart Register
	unsigned int WDT_STAT;		//Interrupt status Register
	unsigned int WDT_EOI;		//Interrupt clear Register
}WDT_reg;

#define WDT0	((WDT_reg*)WDT0_BASE)
#define WDT1	((WDT_reg*)WDT1_BASE)
void wdt_init();

#endif 
