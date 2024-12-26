//采用行为描述方式实现实现例题4.12血型是否相容的电路（采用血型编码I），输入为开发板上最左边的2个拨动开关和最右边的2个开关，输出为开发板上最左边的LED灯。

`timescale 1ns / 1ps	

module example_4_12a_1(
    input sw_pin[7:0],            	                   		 //8个拨动开关
    output reg [15:0] led_pin    		 	//16个led灯            
);

    always @(*)					//行为描述方式 
    begin
            if((sw_pin[0]==0 & sw_pin[1]==0) & (sw_pin[6]==0 & sw_pin[7]==0) | (sw_pin[0]==0 & sw_pin[1]==0) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==0 & sw_pin[1]==1) & (sw_pin[6]==0 & sw_pin[7]==1) | (sw_pin[0]==0 & sw_pin[1]==1) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==0) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==0 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==0 & sw_pin[7]==1) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==1 & sw_pin[7]==1)) 
                  		led_pin[0] <= 1;			    
            else
			led_pin[0] <= 0;
    end

endmodule