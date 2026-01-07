.text
.global _start

_start:	
	//----------------设置 LED1(GPIO4_DDR_C6) 为高电平（输出模式）
	ldr x0,=0xFF790004
	ldr w1,[x0]
	orr w1,w1,#(0x1 << 22)	//w1的第22位置1
	str w1,[x0]

	//----------------设置 LED2(GPIO0_DDR_A2) 为高电平（输出模式）
	ldr x0,=0xFF720004
	ldr w1,[x0]
	orr w1,w1,#(0x1 << 2)            //w1的第2位置1
	str w1,[x0]

	//----------------设置 LED3(GPIO0_DDR_B4) 为高电平（输出模式）
	ldr x0,=0xFF720004
	ldr w1,[x0]
	orr w1,w1,#(0x1 << 12)            //w1的第12位置1
	str w1,[x0]

LOOP:
//-----------------------------------LED1(GPIO4_C6)-----------------------------------------------------
	//设置LED1(GPIO4_DR_C6)为高电平（LED1点亮）
	ldr x0,=0xFF790000  	
	ldr w1,[x0]
	orr w1,w1,#(0x1 << 22)	//w1的第22位置1
	str w1,[x0]

	//延时		
    	ldr w3,=0x04FFFFFF   	//设置一个计数值
LOOP5:
    	sub w3,w3,#1
    	cmp w3,#0
    	bne LOOP5	

	//设置LED1(GPIO4_DR_C6)为低电平（LED1熄灭）
	ldr x0,=0xFF790000  	
	ldr w1,[x0]
	ldr w2,=0xFFBFFFFF
	and w1,w1,w2		//w1的第22位置0
    	str w1,[x0]

	//延时
	ldr w3,=0x04FFFFFF   	//设置一个计数值
LOOP6:	
	sub w3,w3,#1
    	cmp w3,#0
                bne LOOP6
//------------------------------------------------------------------------------------------------------------

//---------------------------------------LED2(GPIO0_A2)--------------------------------------------------
	//设置 LED2(GPIO0_DR_A2)为高电平（LED2点亮）
	ldr x0,=0xFF720000  	
	ldr w1,[x0]
	orr w1,w1,#(0x1 << 2)	//w1的第2位置1
	str w1,[x0]

	//延时
	ldr w3,=0x04FFFFFF   	//设置一个计数值
LOOP3:	
	sub w3,w3,#1
    	cmp w3,#0
                bne LOOP3

	//设置 LED2(GPIO0_DR_A2)为低电平（LED2熄灭）
	ldr x0,=0xFF720000  	
	ldr w1,[x0]
	ldr w2,=0xFFFFFFFB
	and w1,w1,w2		//w1的第2位置0
    	str w1,[x0]	

	//延时
	ldr w3,=0x04FFFFFF   	//设置一个计数值
LOOP4:	
	sub w3,w3,#1
    	cmp w3,#0
                bne LOOP4
//-----------------------------------------------------------------------------------------------------------

//------------------------------------ LED3(GPIO0_B4)----------------------------------------------------
	//设置 LED3(GPIO0_DR_B4)为高电平（LED3点亮） 
	ldr x0,=0xFF720000  	
	ldr w1,[x0]
	orr w1,w1,#(0x1 << 12)	//w1的第12位置1
	str w1,[x0]

	//延时
	ldr w3,=0x04FFFFFF   	//设置一个计数值
LOOP1:	
	sub w3,w3,#1
    	cmp w3,#0
                bne LOOP1

	//设置 LED3(GPIO0_DR_B4)为低电平（LED3熄灭） 
	ldr x0,=0xFF720000  	
	ldr w1,[x0]
	ldr w2,=0xFFFFEFFF
	and w1,w1,w2		//w1的第12位置0
    	str w1,[x0]	

	//延时
	ldr w3,=0x04FFFFFF   	//设置一个计数值
LOOP2:	
	sub w3,w3,#1
    	cmp w3,#0
                bne LOOP2
//-----------------------------------------------------------------------------------------		

    	b LOOP

stop:
	b stop
