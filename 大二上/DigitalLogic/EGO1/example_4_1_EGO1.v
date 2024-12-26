//结构化描述方式（子模块采用行为描述方式）实现例题4.1的不一致电路，输入为最左边的3个拨动开关，输出为最左边的LED灯。

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

module or_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= a | b; 
    end
endmodule

module nand_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= ~(a & b); 
    end
endmodule

module example_4_1(
    input sw_pin[7:0],                               		 //8个拨动开关
    output [15:0] led_pin    		 	//16个led灯            
);
    wire p1, p2, p3, p4, p5;
    not_gate U1(.a(sw_pin[0]),.f(p1));				//结构化描述方式
    or_gate U2(.a(sw_pin[1]),.b(sw_pin[2]),.f(p2));			//结构化描述方式
    nand_gate U3(.a(sw_pin[1]),.b(sw_pin[2]),.f(p3));		//结构化描述方式
    nand_gate U4(.a(p1),.b(p2),.f(p4));				//结构化描述方式
    nand_gate U5(.a(p3),.b(sw_pin[0]),.f(p5));			//结构化描述方式
    nand_gate U6(.a(p4),.b(p5),.f(led_pin[0]));			//结构化描述方式
endmodule