//输入（x）为开发板上的KEY1按键，状态（y3、y2、y1）和输出Z为开发板上最左边的3个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module and_gate(
    input a,
    input b,
    input c,
	input d,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= a & b & c & d; 
    end
    assign f = y;
endmodule

module t_flip_flop(
    input t,                               	  
    input cp,
    input reset,                                                         
    output q, qn		
);
    reg y;
    always @(negedge cp or negedge reset)                     //行为描述方式
    begin
        if (reset==0)
            y <= 0;
        else
                case({t})
	               1: y <= ~y;			      //  t = 1       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_4_2(
    input x,                               		 
    input y3,y2, y1,
    input reset,				
//    output ny3,ny2, ny1, z
    
    output ny1,ny2,ny3, z 		 	        
);
    wire ny3n,ny2n, ny1n;

    t_flip_flop U1(.t(1),.cp(x),.reset(reset),.q(ny1),.qn(ny1n));		//结构化描述方式
    t_flip_flop U2(.t(1),.cp(y1),.reset(reset),.q(ny2),.qn(ny2n));		//结构化描述方式
	t_flip_flop U3(.t(1),.cp(y2),.reset(reset),.q(ny3),.qn(ny3n));		//结构化描述方式
    and_gate U4(.a(x),.b(y1),.c(y2),.d(y3),.f(z));				//结构化描述方式

endmodule