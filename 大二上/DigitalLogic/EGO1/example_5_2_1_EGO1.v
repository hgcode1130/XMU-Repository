//行为描述方式实现例题5.2的“101”序列检测器，输入x和CP为开发板上最左边的拨动开关以及S1按键，状态（y2、y1）和输出Z为开发板上最左边的2个LED灯以及最右边的LED灯。

`timescale 1ns / 1ps	

module example_5_2_1(
    input cp,
    input x,        
    input rd,                       		 	
    input y2, y1,			 
    output reg ny2, ny1, z    		 	          
);

    always @(posedge cp  or negedge rd)                      //行为描述方式

    begin
       if(rd==0)  	                                           	        //  rd=0         
                begin ny2 <= 0; ny1 <= 0; z=0; end
       else                                                                           //  rd=1            
                case({y2, y1, x})
	                0: begin ny2 <= 0; ny1 <= 0; z=0; end			      //  y2 y1 x = 000       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 0; ny1 <= 1; z=0;  end			      //  y2 y1 x = 001       y2n+1 y1n+1 = 01       z=0	               
		2: begin ny2 <= 1; ny1 <= 0; z=0;  end			      //  y2 y1 x = 010       y2n+1 y1n+1 = 10       z=0	               
		3: begin ny2 <= 0; ny1 <= 1; z=0;  end			      //  y2 y1 x = 011       y2n+1 y1n+1 = 01       z=0           
		4: begin ny2 <= 0; ny1 <= 0; z=0;  end			      //  y2 y1 x = 100       y2n+1 y1n+1 = 00       z=0	               
		5: begin ny2 <= 0; ny1 <= 1; z=1;  end			      //  y2 y1 x = 101       y2n+1 y1n+1 = 01       z=1	               
		6: begin ny2 <= 0; ny1 <= 0; z=0;  end			      //  y2 y1 x = 110       y2n+1 y1n+1 = 00       z=0
		7: begin ny2 <= 0; ny1 <= 1; z=0;  end			      //  y2 y1 x = 111       y2n+1 y1n+1 = 01       z=0
                endcase
    end

endmodule