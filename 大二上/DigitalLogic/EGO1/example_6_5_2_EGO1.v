//结构化描述方式（子模块采用行为描述方式）实现例题6.5的“00->10->11”序列检测器，输入（x1、x2）为开发板上的最左边的2个拨动开关，状态（y2、y1）和输出Z为开发板上最左边的2个LED灯以及最右边的1个LED灯。

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

module and_gate2(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= a & b; 
    end
    assign f = y;
endmodule

module and_gate3(
    input a,
    input b,
    input c,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= a & b & c; 
    end
    assign f = y;
endmodule

module or_gate2(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= a | b; 
    end
    assign f = y;
endmodule

module example_6_5_2(
    input x2, x1,                         		 
    input y2, y1,				
    output ny2, ny1, z    	
);

    wire t1, t2, t3, t4, t5;

    not_gate U1(.a(x1),.f(t1));					//结构化描述方式
    not_gate U2(.a(y1),.f(t2));					//结构化描述方式

    and_gate2 U3(.a(x2),.b(y1),.f(t3));				//结构化描述方式

    and_gate3 U4(.a(t1),.b(t2),.c(x2),.f(t4));			//结构化描述方式
    and_gate3 U5(.a(x1),.b(x2),.c(y2),.f(t5));			//结构化描述方式

    or_gate2 U6(.a(x1),.b(t3),.f(ny1));				//结构化描述方式
    or_gate2 U7(.a(t4),.b(t5),.f(ny2));				//结构化描述方式

    and_gate2 U8(.a(y1),.b(y2),.f(z));				//结构化描述方式

endmodule