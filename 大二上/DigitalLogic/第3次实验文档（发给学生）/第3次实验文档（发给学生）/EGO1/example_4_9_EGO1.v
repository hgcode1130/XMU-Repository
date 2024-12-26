//结构化描述方式（子模块采用行为描述方式）实现例题4.9的全加器电路，输入为开发板上最左边的3个拨动开关，输出为开发板上最左边的2个LED灯（电路I）和最右边的2个LED灯（电路II）。

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

module xor_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= a ^ b; 
    end
endmodule

module example_4_9(
    input sw_pin[7:0],                               		 //8个拨动开关
    output [15:0] led_pin    		 	//16个led灯            
);
    wire p1, p2, p3, p4, p5, p6, p7;

    xor_gate U1(.a(sw_pin[0]),.b(sw_pin[1]),.f(p1));					//结构化描述方式
    nand2_gate U2(.a(sw_pin[0]),.b(sw_pin[1]),.f(p2));				//结构化描述方式
    nand2_gate U3(.a(sw_pin[0]),.b(sw_pin[2]),.f(p3));				//结构化描述方式
    nand2_gate U4(.a(sw_pin[1]),.b(sw_pin[2]),.f(p4));				//结构化描述方式
    xor_gate U5(.a(p1),.b(sw_pin[2]),.f(led_pin[0]));					//结构化描述方式
    nand3_gate U6(.a(p2),.b(p3),.c(p4),.f(led_pin[1]));				//结构化描述方式

    xor_gate U7(.a(sw_pin[0]),.b(sw_pin[1]),.f(p5));					//结构化描述方式
    nand2_gate U8(.a(p5),.b(sw_pin[2]),.f(p6));					//结构化描述方式
    nand2_gate U9(.a(sw_pin[0]),.b(sw_pin[1]),.f(p7));				//结构化描述方式
    xor_gate U10(.a(p5),.b(sw_pin[2]),.f(led_pin[6]));				//结构化描述方式
    nand2_gate U11(.a(p6),.b(p7),.f(led_pin[7]));					//结构化描述方式

endmodule