//结构化描述方式实现例题4.16的组合逻辑电路（增加冗余项前），以及增加冗余项后的组合逻辑电路（增加冗余项后），输入为开发板上最左边的3个拨动开关，输出为开发板上最左边的LED灯（增加冗余项前）和最右边的LED灯（增加冗余项前）。

`timescale 1ns / 1ps	

module not_gate(
    input a,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= ~a; 
    end
endmodule

module nand2_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= ~(a & b); 
    end
endmodule

module nand3_gate(
    input a,
    input b,
    input c,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= ~(a & b & c); 
    end
endmodule

module example_4_16(
    input sw_pin[7:0],                               		 //8个拨动开关
    output [15:0] led_pin    		 	//16个led灯            
);
    wire p1, p2, p3, p4, p5, p6, p7;

    nand2_gate U1(.a(sw_pin[1]),.b(sw_pin[0]),.f(p1));				//结构化描述方式
    not_gate U2(.a(sw_pin[0]),.f(p2));						//结构化描述方式
    nand2_gate U3(.a(p2),.b(sw_pin[2]),.f(p3));					//结构化描述方式
    nand2_gate U4(.a(p1),.b(p3),.f(led_pin[0]));					//结构化描述方式

    nand2_gate U5(.a(sw_pin[1]),.b(sw_pin[0]),.f(p4));				//结构化描述方式
    not_gate U6(.a(sw_pin[0]),.f(p5));						//结构化描述方式
    nand2_gate U7(.a(p5),.b(sw_pin[2]),.f(p6));					//结构化描述方式
    nand2_gate U8(.a(sw_pin[2]),.b(sw_pin[1]),.f(p7));				//结构化描述方式
    nand3_gate U9(.a(p4),.b(p6),.c(p7),.f(led_pin[7]));				//结构化描述方式

endmodule