//结构化描述方式（子模块采用行为描述方式）实现例题6.2的模4加1计数器，输入（x1、x2、x3）为开发板上的S3、S2、S0按键，状态（y2、y1）和输出Z为开发板上最左边的2个LED灯以及最右边的1个LED灯。

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

module nor_gate2(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~(a | b); 
    end
    assign f = y;
endmodule

module nor_gate3(
    input a,
    input b,
    input c,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~(a | b | c); 
    end
    assign f = y;
endmodule

module rs_flip_flop(
    input r, s,          
    output q, qn		
);
    reg y;

    always @(*)                     //行为描述方式
    begin
                case({r,s})
	               0: y <= 1'bx;		      //  RS  =  00       Y=不定
	               1: y <= 0;			      //  RS  =  01       Y=0
	               2: y <= 1;			      //  RS  =  10       Y=1
                endcase
    end

    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_2(
    input x1, x2, x3,                               		 
    input y2, y2n, y1, y1n,				
    output ny2, ny1, z    	
);

    wire s2, r2, s1, r1, t1, t2, t3, t4; 
    wire ny2n, ny1n;

    not_gate U1(.a(x1),.f(s2));					//结构化描述方式
    and_gate2 U2(.a(x3),.b(x3),.f(t1));				//结构化描述方式
    and_gate2 U3(.a(x2),.b(y1),.f(t2));				//结构化描述方式
    nor_gate2 U4(.a(t1),.b(t2),.f(r2));				//结构化描述方式
    nand_gate3 U5(.a(x2),.b(y2),.c(y1n),.f(s1));			//结构化描述方式
    and_gate2 U6(.a(x1),.b(x1),.f(t3));				//结构化描述方式
    and_gate2 U7(.a(x3),.b(y2n),.f(t4));				//结构化描述方式
    and_gate2 U8(.a(y1),.b(y1),.f(t5));				//结构化描述方式
    nor_gate3 U9(.a(t3),.b(t4),.c(t5),.f(r1));			//结构化描述方式
    rs_flip_flop U10(.r(r2),.s(s2),.q(ny2),.qn(ny2n));			//结构化描述方式
    rs_flip_flop U11(.r(r1),.s(s1),.q(ny1),.qn(ny1n));			//结构化描述方式
    nor_gate2 U12(.a(y2),.b(y1n),.f(z));				//结构化描述方式

endmodule

module example_6_2_exe(
    input btn_3, btn_2, btn_0,				 //3个按钮
    output [15:0] led_pin    		 		//16个led灯            
);

    reg y2, y2n, y1, y1n;

    example_6_2 U(.x1(btn_3), .x2(btn_2), .x3(btn_0), .y2(y2), .y2n(y2n), .y1(y1), .y1n(y1n), .ny2(led_pin[0]), .ny1(led_pin[1]), .z(led_pin[7]));

    initial begin
        y2=0;
        y2n=1;
        y1=0;
        y1n=1;
    end

    always @(*)                     		//行为描述方式
    begin
	y2 <= led_pin[0];
	y2n <= ~led_pin[0];
	y1 <= led_pin[1];
	y1n <= ~led_pin[1];
    end

endmodule