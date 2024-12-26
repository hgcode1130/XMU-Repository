//结构化描述方式实现4个2输入与非门，输入为左边的8个拨动开关，输出为左边的LED灯中的4个。

`timescale 1ns / 1ps	

module nandgate(
    input a,
    input b,
    output f
);

    assign f = ~(a & b); 	//数据流描述方式

endmodule

module ttl7400_2(
    input sw_pin[7:0],                               		 //8个拨动开关
    output [15:0] led_pin    		 	//16个led灯
);

    nandgate U1(.a(sw_pin[0]),.b(sw_pin[1]),.f(led_pin[0]));		//结构化描述方式
    nandgate U2(.a(sw_pin[2]),.b(sw_pin[3]),.f(led_pin[2]));		//结构化描述方式
    nandgate U3(.a(sw_pin[4]),.b(sw_pin[5]),.f(led_pin[4]));		//结构化描述方式
    nandgate U4(.a(sw_pin[6]),.b(sw_pin[7]),.f(led_pin[6]));		//结构化描述方式

endmodule