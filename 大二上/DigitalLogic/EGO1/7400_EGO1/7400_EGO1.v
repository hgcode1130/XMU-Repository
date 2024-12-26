//数据流描述方式实现4个2输入与非门，输入为左边的8个拨动开关，输出为左边的LED灯中的4个。

`timescale 1ns / 1ps	

module ttl7400(
    input sw_pin[7:0],                                //8个拨动开关
    output [15:0] led_pin    		 //16个led灯
);

    assign led_pin[0] = ~(sw_pin[0] & sw_pin[1]); 		//数据流描述方式
    assign led_pin[2] = ~(sw_pin[2] & sw_pin[3]); 		//数据流描述方式
    assign led_pin[4] = ~(sw_pin[4] & sw_pin[5]); 		//数据流描述方式
    assign led_pin[6] = ~(sw_pin[6] & sw_pin[7]);		//数据流描述方式

endmodule