//行为描述方式实现钟控R-S触发器，输入R、S为最左边的2个拨动开关，CP为S1按键，输出/Q、Q为最左边的2个LED灯

`timescale 1ns / 1ps	

module clk_rs_flip_flop(
    input [7:0] sw_pin,                               	//8个拨动开关    
    input btn_1,                                                         //按键开关S1
    output [15:0] led_pin    			//16个led灯
);

    reg q;

    always @(posedge btn_1)
    begin
       case({sw_pin[0],sw_pin[1]})
	       1: q <= 1;
	       2: q <= 0;
	       3: q <= 1'bx;
       endcase
    end

    assign led_pin[1] = q;
    assign led_pin[0] = ~q;

endmodule