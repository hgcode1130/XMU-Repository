//采用行为描述方式实现例题6.1的模4加1计数器，输入（x）为开发板上的S1按键，状态（y2、y1）和输出Z为开发板上最左边的2个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module example_6_1_3(
    input x,                               		 
    input y2, y1,	
    input rd,			
    output reg ny2, ny1, z    		 	        
);

    always @(negedge x or negedge rd)                      //行为描述方式

    begin
       if(rd==0)  	                                           	        //  rd=0         n2y=0  ny1=0  z=0
                begin ny2 <= 0; ny1 <= 0; z <= 0; end
       else                                                                           //  rd=1            
                case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 01       z=0
	                1: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 10       z=0	               
		2: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 11       z=0	               
		3: begin ny2 <= 0; ny1 <= 0; z <= 1; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 00       z=1	               
                endcase
    end

endmodule