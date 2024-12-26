//��Ϊ������ʽʵ���ӿ�R-S������������R��SΪ����ߵ�2���������أ�CPΪS1���������/Q��QΪ����ߵ�2��LED��

`timescale 1ns / 1ps	

module clk_rs_flip_flop(
    input [7:0] sw_pin,                               	//8����������    
    input btn_1,                                                         //��������S1
    output [15:0] led_pin    			//16��led��
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