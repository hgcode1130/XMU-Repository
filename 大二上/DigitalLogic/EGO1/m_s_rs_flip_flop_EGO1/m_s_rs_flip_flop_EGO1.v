//行为描述方式实现主从R-S触发器，输入R、S为最左边的2个拨动开关，输入RD、SD为最右边的2个拨动开关，CP为S1按键，输出/Q、Q为最左边的2个LED灯

`timescale 1ns / 1ps	

module m_s_rs_flip_flop(
    input [7:0] sw_pin,                               	//8个拨动开关    
    input btn_1,                                                         //按键开关S1
    output [15:0] led_pin    			//16个led灯
);

    reg q;

    always @(negedge btn_1 or negedge sw_pin[6] or negedge sw_pin[7])
    begin
       if(sw_pin[6]==0)                                                     //  RD=0    SD=X         Q=0
            q <= 0;
       else if(sw_pin[6]==1 & sw_pin[7]==0)                  //  RD=1    SD=0         Q=1
            q <= 1;
       else                                                                         //  RD=1    SD=1         
           begin
                case({sw_pin[0],sw_pin[1]})
	               1: q <= 1;			    //  RS  =  01       Q=1
	               2: q <= 0;			    //  RS  =  10       Q=0
	               3: q <= 1'bx;		    //  RS  =  11       Q=d
                endcase
           end
    end

    assign led_pin[1] = q;
    assign led_pin[0] = ~q;

endmodule