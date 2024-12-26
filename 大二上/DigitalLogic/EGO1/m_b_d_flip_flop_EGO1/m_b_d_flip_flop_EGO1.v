//��Ϊ������ʽʵ��ά��-����D������������DΪ����ߵĲ������أ�����RD��SDΪ���ұߵ�2���������أ�CPΪS1���������/Q��QΪ����ߵ�2��LED��

`timescale 1ns / 1ps	

module m_s_rs_flip_flop(
    input [7:0] sw_pin,                               	//8����������    
    input btn_1,                                                         //��������S1
    output [15:0] led_pin    			//16��led��
);

    reg q;

    always @(posedge btn_1 or negedge sw_pin[6] or negedge sw_pin[7])
    begin
       if(sw_pin[6]==0)                                                     //  RD=0    SD=X         Q=0
            q <= 0;
       else if(sw_pin[6]==1 & sw_pin[7]==0)                  //  RD=1    SD=0         Q=1
            q <= 1;
       else                                                                         //  RD=1    SD=1         
           begin
                case(sw_pin[0])
	               0: q <= 0;			       //  D  =  0       Q=0
	               1: q <= 1;			       //  D  =  1       Q=1
                endcase
           end
    end

    assign led_pin[1] = q;
    assign led_pin[0] = ~q;

endmodule