
`timescale 1ns / 1ps

module ttl74153(
    input [7:0] sw_pin,					//8个拨动开关
    output [15:0] led_pin
);
    reg y;
    always @(*)                        //行为描述方式
    begin
                case({sw_pin[0],sw_pin[1],sw_pin[2]})
	               0: 	y <= sw_pin[7];			    
	               1: 	y <= sw_pin[6];			    
	               2: 	y <= sw_pin[5];			    
	               3: 	y <= sw_pin[4];			    
	               default:     y <= 0;			    //  左边的4个数码管全灭
                endcase
    end
        assign led_pin[0]=y;
 endmodule