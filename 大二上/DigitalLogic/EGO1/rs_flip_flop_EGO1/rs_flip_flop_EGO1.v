//行为描述方式实现与非门构成的基本R-S触发器，2个输入为最左边的2个拨动开关，输出为最左边的LED灯

`timescale 1ns / 1ps	

module rs_flip_flop(
    input [7:0] sw_pin,                               	//8个拨动开关
    output reg [15:0] led_pin    		//16个led灯
);

always @(*)
    begin

      if(sw_pin[0]==0 & sw_pin[1]==1)		//R S =0 1             /Q=1    Q=0     
         begin 
              led_pin[0] <= 1; 			//    输出 /Q
              led_pin[1] <= 0; 			//    输出  Q
         end

      if(sw_pin[0]==1 & sw_pin[1]==0)		//R S =1 0             /Q=0    Q=1     
         begin 
              led_pin[0] <= 0; 			//    输出 /Q
              led_pin[1] <= 1; 			//    输出  Q
         end

      if(sw_pin[0]==0 & sw_pin[1]==0)		//R S =0 0             /Q=不定    Q=不定     
         begin 
              led_pin[0] <= 1'bx; 			//    输出 /Q
              led_pin[1] <= 1'bx; 			//    输出  Q
         end

    end

endmodule