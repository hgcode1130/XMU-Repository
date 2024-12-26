//行为描述方式实现4个2输入与非门，输入为左边的8个拨动开关，输出为左边的LED灯中的4个。

`timescale 1ns / 1ps	

module ttl7400_1(
    input sw_pin[7:0],                               		 //8个拨动开关
    output reg [15:0] led_pin    		 //16个led灯
);

always @(*)			//行为描述方式
begin
    led_pin[0] <= ~(sw_pin[0] & sw_pin[1]); 
    led_pin[2] <= ~(sw_pin[2] & sw_pin[3]); 
    led_pin[4] <= ~(sw_pin[4] & sw_pin[5]); 
    led_pin[6] <= ~(sw_pin[6] & sw_pin[7]); 
end

endmodule