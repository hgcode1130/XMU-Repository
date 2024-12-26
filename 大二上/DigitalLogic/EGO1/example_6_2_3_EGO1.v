//行为描述方式实现例题6.2的模4加1计数器，输入（x1、x2、x3）为开发板上的S3、S2、S0按键，状态（y2、y1）和输出Z为开发板上最左边的2个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module example_6_2_3(
    input x1, x2, x3,                               		 
    input y2, y1,	
    input rd,			
    output reg ny2, ny1, z    		 	        
);

    always @(*)                      //行为描述方式
    begin
    if(rd==0)
        begin ny2 <= 1; ny1 <= 0; z <= 0; end
    else
        begin
	if(x1==1 & x2==0 & x3==0) begin
                        case({y2, y1})
	                0: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 10       z=0
	                1: begin ny2 <= 1; ny1 <= 0; z <= 1; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 10       z=1	               
		2: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 10       z=0	               
		3: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 10       z=0	               
                        endcase
                end

	if(x1==0 & x2==1 & x3==0) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 0; ny1 <= 0; z <= 1; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 00       z=1	               
		2: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 11       z=0	               
		3: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 00       z=0	               
                        endcase
                end

	if(x1==0 & x2==0 & x3==1) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 0; ny1 <= 0; z <= 1; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 00       z=1	               
		2: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 00       z=0	               
		3: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 01       z=0	               
                        endcase
                end
        end
    end

endmodule