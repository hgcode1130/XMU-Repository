//采用行为描述方式实现9.1小节的简单运算器电路，输入为开发板上8个拨动开关、8个DIP开关、4个按键，输出为开发板上最左边的4个LED灯。
//最左边的4个拨动开关为输入A，最右边的4个拨动开关为输入B，最左边的4个DIP开关为输入C，最右边的4个DIP开关为输入D，按键S4为加法运算、按键S1为减法运算、按键S3为与运算、按键S0为异或运算。

`timescale 1ns / 1ps	

module example_9_1(
    input sw_pin[7:0],            	                   		 //8个拨动开关
    input dip_pin[7:0],                                                               //8个DIP开关
    input btn_0, btn_1, btn_3, btn_4,                                        //S0、S1、S3、S4按键
    output reg [15:0] led_pin    		 	//16个led灯            
);

    always @(*)					//行为描述方式 
    begin
	if(btn_4 == 1)
		begin 
			{led_pin[0], led_pin[1], led_pin[2], led_pin[3]} <= {sw_pin[0], sw_pin[1], sw_pin[2], sw_pin[3]} + {sw_pin[4], sw_pin[5], sw_pin[6], sw_pin[7]};
		end
	if(btn_1 == 1)
		begin 
			{led_pin[0], led_pin[1], led_pin[2], led_pin[3]} <= {sw_pin[0], sw_pin[1], sw_pin[2], sw_pin[3]} - {sw_pin[4], sw_pin[5], sw_pin[6], sw_pin[7]};
		end
	if(btn_3 == 1)
		begin 
			led_pin[0] <= sw_pin[0] & dip_pin[0];
			led_pin[1] <= sw_pin[1] & dip_pin[1];
			led_pin[2] <= sw_pin[2] & dip_pin[2];
			led_pin[3] <= sw_pin[3] & dip_pin[3];
		end
	if(btn_0 == 1)
		begin 
			led_pin[0] <= sw_pin[0] ^ dip_pin[4];
			led_pin[1] <= sw_pin[1] ^ dip_pin[5];
			led_pin[2] <= sw_pin[2] ^ dip_pin[6];
			led_pin[3] <= sw_pin[3] ^ dip_pin[7];
		end
    end

endmodule