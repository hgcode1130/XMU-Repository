#include "fs3399_uart.h"
#include "fs3399_grf.h"

//串口初始化函数
void fs_uart_init(unsigned long baudrate)
{
	volatile unsigned int rate;

	/*设置GPIO4_C0 GPIO4_C1 管脚为串口功能*/
	GRF_GPIO4C_IOMUX = (0x3 << 16) | (0x3 << (16+2)) | (0x2 << 0) | (0x2 << 2);
	
	/*软件复位uart rcvr_fifo xmit_fifo*/
	UART2_SRR = (0x1 << 0) | (0x1 << 1) | (0x1 << 2); 

	/*禁止中断：用轮询的方式*/
	UART2_IER = 0x00;

	/*调制解调器控制寄存器禁用*/
	UART2_MCR = 0x00;

	/* 设置串口协议*/
	UART2_LCR &= (~(0x3 << 0));			
    	UART2_LCR |=  (0x3 << 0); 			//设置数据长度 : 8 bit
    	UART2_LCR &= (~(0x1 << 2)); 		//设置停止位 : 1 stop bit
    	UART2_LCR &= (~(0x1 << 3)); 		//禁止校验位

	/* 计算波特率：本实验的波特率为115200*/
	rate =  24000000/16/baudrate;		//baud rate = 24000000/16/rate;

	UART2_LCR |= (0x01 << 7);			//该位用于启用除数锁存寄存器(DLL和DLH)的读写//以设置UART的波特率									
    	UART2_DLL = (rate & 0xFF);			//设置波特率
    	UART2_LCR &= ~(0x01 << 7);		//该位必须在初始波特率设置后清除//以便访问其他寄存器					
    	UART2_SFE = 0x1;				//影子FIFO使能
    	UART2_SRT = 0x3;				//设置数据接收触发: FIFO 2 less than full
    	UART2_STET = 0x1;				//设置数据发送触发 : 2 characters in the FIFO
}

//发送字符
void fs_putc(unsigned char byte)
{
	while ((UART2_USR & (0x1 << 1)) == 0);		//判断发送FIFO是否已满

    	UART2_THR = byte;				//FIFO未满，将发送的字符写入到发送寄存器
}

//发送字符串
void fs_puts(char *str)
{
	while (*str != '\0') {
		fs_putc(*str);
		str++;
	}
}

//接收字符
char fs_getc()
{
	while ((UART2_USR & (0x1 << 3)) == 0);		//接收FIFO是否空

	return UART2_RBR;					//接收FIFO不为空，讲述返回
}
