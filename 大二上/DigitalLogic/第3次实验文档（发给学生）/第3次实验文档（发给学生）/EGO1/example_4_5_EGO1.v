//结构化描述方式（子模块采用行为描述方式）实现例题4.5的比较两个3位二进制数是否相等的数值比较器电路，输入为开发板上最左边的3个拨动开关和最右边的3个拨动开关，输出为开发板上最左边的1个LED灯。

`timescale 1ns / 1ps	

module nor_gate(
    input a,
    input b,
    input c,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= ~(a | b | c); 
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

module example_4_5(
    input sw_pin[7:0],                               		 //8个拨动开关
    output [15:0] led_pin    		 	//16个led灯            
);
    wire p1, p2, p3;

    xor_gate U1(.a(sw_pin[0]),.b(sw_pin[5]),.f(p1));				//结构化描述方式
    xor_gate U2(.a(sw_pin[1]),.b(sw_pin[6]),.f(p2));				//结构化描述方式
    xor_gate U3(.a(sw_pin[2]),.b(sw_pin[7]),.f(p3));				//结构化描述方式
    nor_gate U4(.a(p1),.b(p2),.c(p3),.f(led_pin[0]));				//结构化描述方式

endmodule