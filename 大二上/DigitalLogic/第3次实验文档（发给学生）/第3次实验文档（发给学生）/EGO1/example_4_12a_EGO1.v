//结构化描述方式（子模块采用行为描述方式）实现例题4.12血型是否相容的电路（采用血型编码I），输入为开发板上最左边的2个拨动开关和最右边的2个开关，输出为开发板上最左边的LED灯。

`timescale 1ns / 1ps	

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
        f <= ~(a & b &c); 
    end
endmodule

module nand4_gate(
    input a,
    input b,
    input c,
    input d,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= ~(a & b & c & d); 
    end
endmodule

module not_gate(
    input a,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= ~a; 
    end
endmodule

module example_4_12a(
    input sw_pin[7:0],                               		 //8个拨动开关
    output [15:0] led_pin    		 	//16个led灯            
);
    wire p1, p2, p3, p4, p5, p6, p7, p8;

    not_gate U1(.a(sw_pin[0]),.f(p1));					//结构化描述方式
    not_gate U2(.a(sw_pin[1]),.f(p2));					//结构化描述方式
    not_gate U3(.a(sw_pin[7]),.f(p3));					//结构化描述方式
    not_gate U4(.a(sw_pin[6]),.f(p4));					//结构化描述方式

    nand3_gate U5(.a(p1),.b(p2),.c(p3),.f(p5));				//结构化描述方式
    nand2_gate U6(.a(sw_pin[6]),.b(p3),.f(p6));				//结构化描述方式
    nand2_gate U7(.a(sw_pin[0]),.b(sw_pin[1]),.f(p7));			//结构化描述方式
    nand3_gate U8(.a(p4),.b(sw_pin[1]),.c(sw_pin[7]),.f(p8));			//结构化描述方式

    nand4_gate U9(.a(p5),.b(p6),.c(p7),.d(p8),.f(led_pin[0]));			//结构化描述方式

endmodule