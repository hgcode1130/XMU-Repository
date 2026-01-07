#include "fs3399_I2C.h"
#include "fs3399_gpio.h"
#include "fs3399_grf.h"

void i2c_init(void)
{
    PMUGRF_GPIO1B_IOMUX |= ((0xFFFF0000 << 0) | (0x01 << 6) | (0x01 << 8));
    I2C4->CLKDIV = 0x5A;
    I2C4->CLKDIV |= 0x5A << 16;
}

void temp_write(unsigned char addr, unsigned char data)
{
    I2C4->CON &= ~(0x7F << 0);
    I2C4->IPD &= ~(0x7F << 0);
    I2C4->CON |= 0x01 << 0; //使能
    I2C4->CON &= ~(0x03 << 1);
    I2C4->CON |= 0x01 << 3; //开始信号
    while(!(I2C4->IPD & (0x01 << 4))); //等待开始信号发完
    I2C4->IPD |=  (0x01 << 4); //清开始信号标志
    I2C4->TXDATA0 = 0x90 | (addr << 8) | (data << 16);
    I2C4->MTXCNT = 3;
    while(!(I2C4->IPD & (0x01 << 2))); //MTXCNT data transmit finished interrupt pending bit
    I2C4->IPD |=  (0x01 << 2);
    I2C4->CON &= ~(0x01 << 3); //手动清除start(注意:前面的开始信号控制位理论会自动清0,实测没有,这里必须手动清,否则是开始信号)
    I2C4->CON |= (0x01 << 4);
    while(!(I2C4->IPD & (0x01 << 5)));
    I2C4->IPD |=  (0x01 << 5);
}

unsigned short temp_read(unsigned char addr)
{
    I2C4->CON &= ~(0x7F << 0);
    I2C4->IPD &= ~(0x7F << 0);
    I2C4->CON |= 0x01 << 0; //使能
    I2C4->CON |=  (0x01 << 1); //自动发送从机地址和从机寄存器地址
    I2C4->MRXADDR = (0x90 | (1 << 24));
    I2C4->MRXRADDR = (addr | (1 << 24));
    I2C4->CON |=  (0x01 << 3);
    while(!(I2C4->IPD & (0x01 << 4)));
    I2C4->IPD |=  (0x01 << 4);
    I2C4->CON |= (0x01 << 5);
    I2C4->MRXCNT = 2;
    while(!(I2C4->IPD & (0x01 << 3)));
    I2C4->IPD |=  (0x01 << 3);
    I2C4->CON &= ~(0x01 << 3); //手动清除start
    I2C4->CON |= (0x01 << 4);
    while(!(I2C4->IPD & (0x01 << 5)));
    I2C4->IPD |=  (0x01 << 5);
    return (I2C4->RXDATA0 & 0xFFFF);
}
