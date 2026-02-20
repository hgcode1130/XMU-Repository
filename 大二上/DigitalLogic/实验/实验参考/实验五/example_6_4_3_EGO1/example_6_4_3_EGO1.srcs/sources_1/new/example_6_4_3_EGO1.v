//行为描述方式（子模块采用行为描述方式）实现例题6.4的模8加1计数器
//输入（x）为开发板上的KEY1按键，状态（y3、y2、y1）和输出Z为开发板上最左边的3个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module example_6_4_3(
    input x,                               		 
    input y3,y2, y1,				
    output reg ny3,ny2, ny1, z    		 	        
);

    always @(negedge x)                      	//行为描述方式
    begin
                case({y3,y2, y1})
	                0: begin ny3<=0; ny2 <= 0; ny1 <= 1; z <= 0; end			      
	                1: begin ny3<=0; ny2 <= 1; ny1 <= 0; z <= 0; end			     
					2: begin ny3<=0; ny2 <= 1; ny1 <= 1; z <= 0; end          
					3: begin ny3<=1; ny2 <= 0; ny1 <= 0; z <= 0; end
					4: begin ny3<=1; ny2 <= 0; ny1 <= 1; z <= 0; end
					5: begin ny3<=1; ny2 <= 1; ny1 <= 0; z <= 0; end
					6: begin ny3<=1; ny2 <= 1; ny1 <= 1; z <= 0; end
					7: begin ny3<=0; ny2 <= 0; ny1 <= 0; z <= 1; end
                endcase
    end

endmodule