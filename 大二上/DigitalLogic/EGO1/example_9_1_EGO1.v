//������Ϊ������ʽʵ��9.1С�ڵļ���������·������Ϊ��������8���������ء�8��DIP���ء�4�����������Ϊ������������ߵ�4��LED�ơ�
//����ߵ�4����������Ϊ����A�����ұߵ�4����������Ϊ����B������ߵ�4��DIP����Ϊ����C�����ұߵ�4��DIP����Ϊ����D������S4Ϊ�ӷ����㡢����S1Ϊ�������㡢����S3Ϊ�����㡢����S0Ϊ������㡣

`timescale 1ns / 1ps	

module example_9_1(
    input sw_pin[7:0],            	                   		 //8����������
    input dip_pin[7:0],                                                               //8��DIP����
    input btn_0, btn_1, btn_3, btn_4,                                        //S0��S1��S3��S4����
    output reg [15:0] led_pin    		 	//16��led��            
);

    always @(*)					//��Ϊ������ʽ 
    begin
	if(btn_4 == 1)
		begin 
			{led_pin[0], led_pin[1], led_pin[2], led_pin[3]} <= {sw_pin[0], sw_pin[1], sw_pin[2], sw_pin[3]} + {sw_pin[4], sw_pin[5], sw_pin[6], sw_pin[7]};
		end
	if(btn_1 == 1)
		begin 
			{led_pin[0], led_pin[1], led_pin[2], led_pin[3]} <= {sw_pin[0], sw_pin[1], sw_pin[2], sw_pin[3]} - {sw_pin[4], sw_pin[5], sw_pin[6], sw_pin[7]};
		end
	if(btn_3 == 1)
		begin 
			led_pin[0] <= sw_pin[0] & dip_pin[0];
			led_pin[1] <= sw_pin[1] & dip_pin[1];
			led_pin[2] <= sw_pin[2] & dip_pin[2];
			led_pin[3] <= sw_pin[3] & dip_pin[3];
		end
	if(btn_0 == 1)
		begin 
			led_pin[0] <= sw_pin[0] ^ dip_pin[4];
			led_pin[1] <= sw_pin[1] ^ dip_pin[5];
			led_pin[2] <= sw_pin[2] ^ dip_pin[6];
			led_pin[3] <= sw_pin[3] ^ dip_pin[7];
		end
    end

endmodule