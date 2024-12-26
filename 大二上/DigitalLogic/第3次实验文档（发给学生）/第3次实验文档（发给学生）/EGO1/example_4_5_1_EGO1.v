//采用行为描述方式实现例题4.5的数值比较器电路，输入为开发板上最左边的3个拨动开关和最右边的3个拨动开关，输出为开发板上最左边的1个LED灯。

`timescale 1ns / 1ps	

module example_4_5_1(
    input sw_pin[7:0],            	                   		 //8个拨动开关
    output reg [15:0] led_pin    		 	//16个led灯            
);

    always @(*)					//行为描述方式 
    begin
                if(sw_pin[0]==sw_pin[5] & sw_pin[1]==sw_pin[6] & sw_pin[2]==sw_pin[7])
                  		led_pin[0] <= 1;			    
                else
			led_pin[0] <= 0;
    end

endmodule