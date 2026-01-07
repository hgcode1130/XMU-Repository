#include "fs3399_int.h"
#include "fs3399_led_mode.h"

int flag = 0;   //led1状态标志位

void irq_init(void)	
{
}

//使能中断
void enable_interrupts(void)
{
    asm volatile("msr	daifclr, #0x03");
}

// irq interrupt install handle 
void irq_install_handler(int irq, interrupt_handler_t *handler, void *data)
{
    if (g_irq_handler[irq].m_func != handler)
        g_irq_handler[irq].m_func = handler;
}

// enable irq handler 
int irq_handler_enable(int irq)
{
    unsigned long M, N;
    if (irq >= NR_GIC_IRQS)
        return -1;
    M = irq / 32;
    N = irq % 32;
    GICD->ISENABLER[M]  = (0x1 << N);
    return 0;
}

//irq 中断处理函数		
void do_irq(void)
{
    unsigned long nintid;
    unsigned long long irqstat;
    asm volatile("mrs %0, " __stringify(ICC_IAR1_EL1) : "=r" (irqstat));
    nintid = (unsigned long)irqstat & 0x3FF;
    if (nintid < NR_GIC_IRQS)
        g_irq_handler[nintid].m_func((void *)(unsigned long)nintid);
    asm volatile("msr " __stringify(ICC_EOIR1_EL1) ", %0" : : "r" ((unsigned long long)nintid));
    asm volatile("msr " __stringify(ICC_DIR_EL1) ", %0" : : "r" ((unsigned long long)nintid));
    isb();
}

//KEY1中断响应处理逻辑：按键控制亮灭
static void key_led_change(void)
{
    if (GPIO1->INT_STATUS & (0x01 << (8 + 2))) 		//Interrupt status
    {
        GPIO1->PORTA_EOI |= (0x01 << (8 + 2)); 		//Clear interrupt
        if (flag == 0) {
        	led_mode(1);				//LED1灯亮
        	flag = 1;
        } else {
        	led_mode(4);				//LED1灯灭
        	flag = 0;
        }
    }
}

//GPIO1_B2(KEY1)按键中断服务程序
void key_led_irq(void)
{    
    enable_interrupts();	//使能中断
    // GPIO设置 
    GPIO1->SWPORTA_DDR   		&= ~(0x01 << (8 + 2)); 			//should be Input
    GPIO1->INTEN         		|=  (0x01 << (8 + 2)); 			//Interrupt enable
    GPIO1->INTMASK       		&= ~(0x01 << (8 + 2)); 			//Interrupt bits are unmasked
    GPIO1->INTTYPE_LEVEL	 	|=  (0x01 << (8 + 2)); 			//Edge-sensitive
    GPIO1->INT_POLARITY  		&=  ~(0x01 << (8 + 2)); 			//Active-low
    GPIO1->DEBOUNCE     	 	|=  (0x01 << (8 + 2)); 			//Enable debounce
    // 注册中断函数并使能 
    irq_install_handler(GPIO1_INTR, (interrupt_handler_t *)key_led_change, (void *)(0));
    irq_handler_enable(GPIO1_INTR);
}