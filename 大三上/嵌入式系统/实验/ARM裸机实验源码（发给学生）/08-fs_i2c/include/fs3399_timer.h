#ifndef __FS3399_TIMER_H__
#define __FS3399_TIMER_H__

#define  TIMER0_5_BASE              0xFF850000		//timer 0 -5 base addr
#define  TIMER6_11_BASE             0xFF858000		//timer 6 - 11 base addr
#define  CRU_BASE		0xFF760000

typedef volatile struct {
	unsigned int LOAD_COUNT0;      	      //0x0000
	unsigned int LOAD_COUNT1;    	      //0x0004
	unsigned int CURRENT_VALUE0;      	  //0x0008
	unsigned int CURRENT_VALUE1	;         //0x000C
	unsigned int LOAD_COUNT2;      	      //0x0010
	unsigned int LOAD_COUNT3;    	      //0x0014
	unsigned int INTSTATUS;          	  //0x0018
	unsigned int CONTROL_REG;             //0x001C	
} timer_reg;

#define      TIMER0           ((timer_reg*)(TIMER0_5_BASE + 0x20 * 0))
#define      TIMER1           ((timer_reg*)(TIMER0_5_BASE + 0x20 * 1))
#define      TIMER2           ((timer_reg*)(TIMER0_5_BASE + 0x20 * 2))
#define      TIMER3           ((timer_reg*)(TIMER0_5_BASE + 0x20 * 3)) 	//for irq test
#define      TIMER4           ((timer_reg*)(TIMER0_5_BASE + 0x20 * 4)) 	//for delay
#define      TIMER5           ((timer_reg*)(TIMER0_5_BASE + 0x20 * 5))
#define      TIMER6           ((timer_reg*)(TIMER6_11_BASE + 0x20 * 0))
#define      TIMER7           ((timer_reg*)(TIMER6_11_BASE + 0x20 * 1))
#define      TIMER8           ((timer_reg*)(TIMER6_11_BASE + 0x20 * 2))
#define      TIMER9           ((timer_reg*)(TIMER6_11_BASE + 0x20 * 3))
#define      TIMER10          ((timer_reg*)(TIMER6_11_BASE + 0x20 * 4))
#define      TIMER11          ((timer_reg*)(TIMER6_11_BASE + 0x20 * 5))
#define CRU_CLKGATE_CON26		(*((volatile unsigned int *)(CRU_BASE+0x0386)))

void fs_delay_us(volatile unsigned long int  us);
void fs_delay_ms(volatile unsigned long int  ms);
void fs_delay_s(volatile unsigned long int s);

#endif
