#ifndef __FS3399_UART_H__
#define __FS3399_UART_H__

#define    UART0_BASE                0xFF180000     //串口0 基地址
#define    UART1_BASE                0xFF190000     //串口1 基地址
#define    UART2_BASE                0xFF1A0000     //串口2 基地址
#define    UART3_BASE                0xFF1B0000     //串口3 基地址
#define    UART4_BASE                0xFF370000     //串口3 基地址

#define    UART2_RBR            	 (*(volatile unsigned int *)(UART2_BASE + 0x0000))  //Receive Buffer Register
#define    UART2_THR            	 (*(volatile unsigned int *)(UART2_BASE + 0x0000))  //Transmit Holding Register
#define    UART2_DLL            	 	(*(volatile unsigned int *)(UART2_BASE + 0x0000))  //Divisor Latch (Low)
#define    UART2_DLH            	 (*(volatile unsigned int *)(UART2_BASE + 0x0004))  //Divisor Latch (High)
#define    UART2_IER            	 	(*(volatile unsigned int *)(UART2_BASE + 0x0004))  //Interrupt Enable Register 
#define    UART2_LCR            	 	(*(volatile unsigned int *)(UART2_BASE + 0x000C))  //Line Control Register
#define    UART2_MCR            	 (*(volatile unsigned int *)(UART2_BASE + 0x0010))  //Modem Control Register
#define    UART2_SRR            	 	(*(volatile unsigned int *)(UART2_BASE + 0x0088))  //Software Reset Register
#define    UART2_USR            	 (*(volatile unsigned int *)(UART2_BASE + 0x007C))  //UART Status Register
#define    UART2_SFE            	 	(*(volatile unsigned int *)(UART2_BASE + 0x0098))  //Shadow FIFO Enable
#define    UART2_SRT            		 (*(volatile unsigned int *)(UART2_BASE + 0x009C))  //Shadow RCVR Trigger
#define    UART2_STET           	 (*(volatile unsigned int *)(UART2_BASE + 0x00A0))  //Shadow TX Empty Trigger

//串口初始化函数
void fs_uart_init();

//发送字节
void fs_putc(unsigned char byte);

//发送字符串
void fs_puts(char *str);

//获取字符
char fs_getc();

#endif 
