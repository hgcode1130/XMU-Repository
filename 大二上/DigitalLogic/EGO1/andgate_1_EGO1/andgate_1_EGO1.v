//行为描述方式实现2输入与门，2个输入为最左边的2个拨动开关，输出为最左边的LED灯

`timescale 1ns / 1ps

module andgate_1(
    input sw_pin[7:0],                              		 //8个拨动开关
    output reg [15:0] led_pin    		//16个led灯
);

always @(*)		//行为描述方式
begin
   led_pin[0] <= sw_pin[0] & sw_pin[1]; 
end

endmodule