//行为描述方式实现例题5.1的2位二进制数可逆计数器，开发板上的输入（x、CP）为开发板上最左边的拨动开关以及S1按键，输出（y2、y1）为开发板上最左边的2个LED灯。

`timescale 1ns / 1ps	

module example_5_1_1(
    input sw_pin[7:0],                               		 	//8个拨动开关
    input btn_1,				 	//1个按钮
    output reg [15:0] led_pin    		 	//16个led灯            
);

    always @(negedge btn_1)                      //行为描述方式

    begin
                case({sw_pin[0], led_pin[0], led_pin[1]})
	                0: begin led_pin[0] <= 0; led_pin[1] <= 1; end			      //  x y2 y1 = 000       y2n+1 y1n+1 = 01
	                1: begin led_pin[0] <= 1; led_pin[1] <= 0; end			      //  x y2 y1 = 001       y2n+1 y1n+1 = 10	               
		2: begin led_pin[0] <= 1; led_pin[1] <= 1; end			      //  x y2 y1 = 010       y2n+1 y1n+1 = 11	               
		3: begin led_pin[0] <= 0; led_pin[1] <= 0; end			      //  x y2 y1 = 011       y2n+1 y1n+1 = 00	               
		4: begin led_pin[0] <= 1; led_pin[1] <= 1; end			      //  x y2 y1 = 100       y2n+1 y1n+1 = 11	               
		5: begin led_pin[0] <= 0; led_pin[1] <= 0; end			      //  x y2 y1 = 101       y2n+1 y1n+1 = 00	               
		6: begin led_pin[0] <= 0; led_pin[1] <= 1; end			      //  x y2 y1 = 110       y2n+1 y1n+1 = 01
		7: begin led_pin[0] <= 1; led_pin[1] <= 0; end			      //  x y2 y1 = 111       y2n+1 y1n+1 = 10
                endcase
    end

endmodule