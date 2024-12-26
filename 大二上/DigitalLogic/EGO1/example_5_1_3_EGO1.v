//行为描述方式实现例题5.1的2位二进制数可逆计数器，开发板上的输入（x、CP）为开发板上最左边的拨动开关以及S1按键，输出（y2、y1）为开发板上最左边的2个LED灯。

`timescale 1ns / 1ps	

module example_5_1_3(
    input cp, x,
    input y2, y1,				 	
    output reg ny2, ny1    		 	          
);

    always @(negedge cp)                      //行为描述方式
    begin
                case({x, y2, y1})
	                0: begin ny2 <= 0; ny1 <= 1; end			      //  x y2 y1 = 000       y2n+1 y1n+1 = 01
	                1: begin ny2 <= 1; ny1 <= 0; end			      //  x y2 y1 = 001       y2n+1 y1n+1 = 10	               
		2: begin ny2 <= 1; ny1 <= 1; end			      //  x y2 y1 = 010       y2n+1 y1n+1 = 11	               
		3: begin ny2 <= 0; ny1 <= 0; end			      //  x y2 y1 = 011       y2n+1 y1n+1 = 00	               
		4: begin ny2 <= 1; ny1 <= 1; end			      //  x y2 y1 = 100       y2n+1 y1n+1 = 11	               
		5: begin ny2 <= 0; ny1 <= 0; end			      //  x y2 y1 = 101       y2n+1 y1n+1 = 00	               
		6: begin ny2 <= 0; ny1 <= 1; end			      //  x y2 y1 = 110       y2n+1 y1n+1 = 01
		7: begin ny2 <= 1; ny1 <= 0; end			      //  x y2 y1 = 111       y2n+1 y1n+1 = 10
                endcase
    end

endmodule

module example_5_1_3_exe(
    input sw_pin[7:0],                               		 //8个拨动开关
    input btn_1,				 //1个按钮
    output [15:0] led_pin    		 	//16个led灯            
);

    reg y2, y1;

    example_5_1_3 U(.cp(btn_1), .x(sw_pin[0]), .y2(y2), .y1(y1), .ny2(led_pin[0]), .ny1(led_pin[1]));

    initial begin
        y2=0;
        y1=0;
    end

    always @(*)                     //行为描述方式
    begin
	y2 <= led_pin[0];
	y1 <= led_pin[1];
    end

endmodule