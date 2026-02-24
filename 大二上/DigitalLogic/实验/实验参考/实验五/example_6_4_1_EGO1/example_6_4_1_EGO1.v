//行为描述方式（子模块采用行为描述方式）实现例题6.4的模8加1计数器
//输入（x）为开发板上的KEY1按键，状态（y3、y2、y1）和输出Z为开发板上最左边的3个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module example_6_4_1(
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

module example_6_4_1_exe(
    input btn_1,				 //KEY1按钮
    output [7:0] led_pin    		 	//8个led灯            
);

    reg y3, y2, y1;

    example_6_4_1 U(.x(btn_1), .y3(y3),.y2(y2), .y1(y1), .ny3(led_pin[7]), .ny2(led_pin[6]), .ny1(led_pin[5]), .z(led_pin[0]));

    initial begin
		y3=0;
        y2=0;
        y1=0;
    end

    always @(*)                     		//行为描述方式
    begin
	y3 <= led_pin[7];
	y2 <= led_pin[6];
	y1 <= led_pin[5];
    end

endmodule