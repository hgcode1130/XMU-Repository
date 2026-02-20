//结构化描述方式（子模块采用行为描述方式）实现例题6.11的单脉冲发生器，输入（x1、x2）为开发板上的最左边的2个拨动开关，状态（y2、y1）和输出Z为开发板上最左边的2个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module not_gate(
    input a,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~a; 
    end
    assign f = y;
endmodule

module nand_gate2(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~(a & b); 
    end
    assign f = y;
endmodule

module nand_gate3(
    input a,
    input b,
    input c,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~(a & b & c); 
    end
    assign f = y;
endmodule


module example_6_11(
    input x1,x2,
	input wire clk,
    input y2, y1,				
    output ny2, ny1, z    	
);

    wire t1, t2, t3, t4, t5, t6, t7;

    not_gate u1(.a(x1),.f(t1));					//结构化描述方式
    not_gate u2(.a(x2),.f(t2));					//结构化描述方式
	
    nand_gate2 U3(.a(x2),.b(y2),.f(t3));
	not_gate U4(.a(t3),.f(z));

    nand_gate3 U5(.a(t1),.b(t2),.c(y1),.f(t4));			//结构化描述方式
    nand_gate2 U6(.a(t3),.b(y1),.f(t5));			//结构化描述方式

    nand_gate2 U7(.a(t4),.b(t3),.f(ny2));				//结构化描述方式
    nand_gate2 U8(.a(t1),.b(t5),.f(ny1));				//结构化描述方式 

endmodule

module example_6_11_exe(
    input btn_1,//btn_2,                               		 	//8个拨动开关
    output [7:0] led_pin    		 		//8个led灯            
);

    reg y2, y1;

    example_6_11 U( .x1(btn_1), .y2(y2), .y1(y1), .ny2(led_pin[7]), .ny1(led_pin[6]), .z(led_pin[0]));

    initial begin
        y2=0;
        y1=0;
    end

    always @(*)                     		//行为描述方式
    begin
	y2 <= led_pin[7];
	y1 <= led_pin[6];
    end

endmodule 