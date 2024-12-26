//数据流描述方式实现2输入与门，2个输入为最左边的2个拨动开关，输出为最左边的LED灯

`timescale 1ns / 1ps	

module andgate(
    input sw_pin[7:0],                               //8个拨动开关
    output [15:0] led_pin    		//16个led灯
);

    assign led_pin[0] = sw_pin[0] & sw_pin[1]; 		//数据流描述方式

endmodule