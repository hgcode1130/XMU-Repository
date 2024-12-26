//采用数据流描述方式实现例题4.16的组合逻辑电路（增加冗余项前），以及增加冗余项后的组合逻辑电路（增加冗余项后），输入为开发板上最左边的3个拨动开关，输出为开发板上最左边的LED灯（增加冗余项前）和最右边的LED灯（增加冗余项前）。

`timescale 1ns / 1ps	

module example_4_16_1(
    input sw_pin[7:0],            	                   		 //8个拨动开关
    output [15:0] led_pin    		 		//16个led灯            
);

    assign led_pin[0] = (sw_pin[0] & sw_pin[1]) | (~sw_pin[0] & sw_pin[2]);  

    assign led_pin[7] = (sw_pin[0] & sw_pin[1]) | (~sw_pin[0] & sw_pin[2]) | (sw_pin[1] & sw_pin[2]);  

endmodule