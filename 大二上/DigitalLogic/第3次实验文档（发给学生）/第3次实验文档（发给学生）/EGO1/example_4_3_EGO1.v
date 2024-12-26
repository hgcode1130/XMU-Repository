//结构化描述方式（子模块采用行为描述方式）实现例题4.3的不一致电路，输入为最左边的4个拨动开关，输出为最左边的4个LED灯。

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

module and_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= a & b; 
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

module example_4_3(
    input sw_pin[7:0],                               		 //8个拨动开关
    output [15:0] led_pin    		 	//16个led灯            
);
    wire p1, p2;

    or_gate U1(.a(sw_pin[2]),.b(sw_pin[3]),.f(p1));				//结构化描述方式
    and_gate U2(.a(sw_pin[1]),.b(p1),.f(p2));				//结构化描述方式
    xor_gate U3(.a(sw_pin[0]),.b(p2),.f(led_pin[0]));				//结构化描述方式
    xor_gate U4(.a(p1),.b(sw_pin[1]),.f(led_pin[1]));				//结构化描述方式
    not_gate U5(.a(sw_pin[3]),.f(led_pin[3]));				//结构化描述方式
    xor_gate U6(.a(sw_pin[2]),.b(led_pin[3]),.f(led_pin[2]));			//结构化描述方式

endmodule