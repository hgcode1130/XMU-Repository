//行为描述方式实现例题5.4的3位串行输入移位寄存器，
//该电路的输入为x，状态为（y3、y2、y1），输出为Z，CP为时钟信号。

`timescale 1ns / 1ps	

module example_5_4_1(
    input sw_pin[7:0],                               		 	//8个拨动开关
    input btn_1,				 	//1个按钮
    output reg [7:0] led_pin    		 		//8个led灯            
);

    always @(negedge btn_1)                      //行为描述方式

    begin
                case({sw_pin[7], led_pin[7], led_pin[6], led_pin[5]})
	    0: begin led_pin[7] <= 0; led_pin[6] <= 0; led_pin[5] <= 0;led_pin[0] <= 0;end			       
	    1: begin led_pin[7] <= 0; led_pin[6] <= 1; led_pin[5] <= 0;led_pin[0] <= 1;end			       
		2: begin led_pin[7] <= 1; led_pin[6] <= 0; led_pin[5] <= 0;led_pin[0] <= 1;end			       
		3: begin led_pin[7] <= 1; led_pin[6] <= 1; led_pin[5] <= 0;led_pin[0] <= 0;end			       
		4: begin led_pin[7] <= 0; led_pin[6] <= 0; led_pin[5] <= 0;led_pin[0] <= 1;end			       
		5: begin led_pin[7] <= 0; led_pin[6] <= 1; led_pin[5] <= 0;led_pin[0] <= 0;end			       
		6: begin led_pin[7] <= 1; led_pin[6] <= 0; led_pin[5] <= 0;led_pin[0] <= 0;end			       
		7: begin led_pin[7] <= 1; led_pin[6] <= 1; led_pin[5] <= 0;led_pin[0] <= 1;end			       
		8: begin led_pin[7] <= 0; led_pin[6] <= 0; led_pin[5] <= 1;led_pin[0] <= 0;end			       
	    9: begin led_pin[7] <= 0; led_pin[6] <= 1; led_pin[5] <= 1;led_pin[0] <= 1;end			       
		10: begin led_pin[7] <= 1; led_pin[6] <= 0; led_pin[5] <= 1;led_pin[0] <= 1;end			       
		11: begin led_pin[7] <= 1; led_pin[6] <= 1; led_pin[5] <= 1;led_pin[0] <= 0;end			       
		12: begin led_pin[7] <= 0; led_pin[6] <= 0; led_pin[5] <= 1;led_pin[0] <= 1;end			       
		13: begin led_pin[7] <= 0; led_pin[6] <= 1; led_pin[5] <= 1;led_pin[0] <= 0;end			       
		14: begin led_pin[7] <= 1; led_pin[6] <= 0; led_pin[5] <= 1;led_pin[0] <= 0;end			       
		15: begin led_pin[7] <= 1; led_pin[6] <= 1; led_pin[5] <= 1;led_pin[0] <= 1;end			       
                endcase
    end

endmodule