//采用数据流描述方式实现例题4.9的全加器FA电路，输入为开发板上最左边的3个拨动开关，输出为开发板上最左边的2个LED灯。

`timescale 1ns / 1ps	

module example_4_9_2(
    input sw_pin[7:0],            	                   		 //8个拨动开关
    output [15:0] led_pin    		 		//16个led灯            
);

    assign {led_pin[1], led_pin[0]} = sw_pin[0] + sw_pin[1] + sw_pin[2];  

endmodule