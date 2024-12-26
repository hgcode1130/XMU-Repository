//结构化描述方式（子模块采用行为描述方式）实现例题6.1的模4加1计数器，输入（x）为开发板上的S1按键，状态（y2、y1）和输出Z为开发板上最左边的2个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module and_gate(
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

module jk_flip_flop(
    input j, k,                               	  
    input cp,                                                         
    output q, qn		
);
    reg y;
    always @(negedge cp)                     //行为描述方式
    begin
                case({j,k})
	               1: y <= 0;			      //  JK  =  01       Y=0
	               2: y <= 1;			      //  JK  =  10       Y=1
	               3: y <= ~y;		      //  JK  =  11       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_1(
    input x,                               		 
    input y2, y1,				
    output ny2, ny1, z    		 	        
);
    wire ny2n, ny1n;

    jk_flip_flop U1(.j(1),.k(1),.cp(x),.q(ny1),.qn(ny1n));		//结构化描述方式
    jk_flip_flop U2(.j(1),.k(1),.cp(y1),.q(ny2),.qn(ny2n));		//结构化描述方式
    and_gate U3(.a(x),.b(y1),.c(y2),.f(z));				//结构化描述方式

endmodule

module example_6_1_exe(
    input btn_1,				 //S1按钮
    output [15:0] led_pin    		 	//16个led灯            
);
    reg y2, y1;
    example_6_1 U(.x(btn_1), .y2(y2), .y1(y1), .ny2(led_pin[0]), .ny1(led_pin[1]), .z(led_pin[7]));
    initial begin
        y2=0;
        y1=0;
    end
    always @(*)                     		//行为描述方式
    begin
	y2 <= led_pin[0];
	y1 <= led_pin[1];
    end
endmodule
