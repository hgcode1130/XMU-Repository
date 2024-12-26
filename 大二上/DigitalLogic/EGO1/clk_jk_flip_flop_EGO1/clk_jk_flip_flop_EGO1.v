//��Ϊ������ʽʵ���ӿ�J-K������������K��JΪ����ߵ�2���������أ�CPΪS1���������/Q��QΪ����ߵ�2��LED��

`timescale 1ns / 1ps	

module clk_jk_flip_flop(
    input [7:0] sw_pin,                               	//8����������    
    input btn_1,                                                         //��������S1
    output [15:0] led_pin    			//16��led��
);

    reg q;

    always @(posedge btn_1)
    begin
       case({sw_pin[1],sw_pin[0]})                //   J K
	       1: q <= 0;                           //   J K=0 1
	       2: q <= 1;                           //    J K=1 0
	       3: q <= ~q;                         //   J K=1 1
       endcase
    end

    assign led_pin[1] = q;
    assign led_pin[0] = ~q;

endmodule