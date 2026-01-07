.text
.global _start

_start:
    //设置 蜂鸣器(GPIO1_DDR_C7) 为高电平（输出模式）
    ldr x0,=0xFF730004
    ldr w1,[x0]
    orr w1,w1,#(0x1 << 23)      //w1的第23位置1
    str w1,[x0]

//------------------LED1(GPIO4_C6)--------------------
    //设置蜂鸣器(GPIO1_DR_C7)输出高电平（蜂鸣器响）
    ldr x0,=0xFF730000
    ldr w1,[x0]
    orr w1,w1,#(0x1 << 23)      //w1的第23位置1
    str w1,[x0]

    //延时
LOOP1:
    ldr w3,=0x0FFFFFFF          //设置一个计数值
    sub w3,w3,#1
    cmp w3,#0
    bne LOOP1

    //设置蜂鸣器(GPIO1_DR_C7)输出低电平（蜂鸣器不响）
    ldr x0,=0xFF730000
    ldr w1,[x0]
    ldr w2,=0xFF7FFFFF
    and w1,w1,w2                //w1的第23位置0
    str w1,[x0]

    //延时
LOOP2:
    ldr w3,=0x0FFFFFFF          //设置一个计数值
    sub w3,w3,#1
    cmp w3,#0
    bne LOOP2

//----------------------------------------------------
stop:
    b stop