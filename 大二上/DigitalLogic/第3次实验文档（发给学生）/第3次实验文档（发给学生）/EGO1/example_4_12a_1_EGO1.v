//������Ϊ������ʽʵ��ʵ������4.12Ѫ���Ƿ����ݵĵ�·������Ѫ�ͱ���I��������Ϊ������������ߵ�2���������غ����ұߵ�2�����أ����Ϊ������������ߵ�LED�ơ�

`timescale 1ns / 1ps	

module example_4_12a_1(
    input sw_pin[7:0],            	                   		 //8����������
    output reg [15:0] led_pin    		 	//16��led��            
);

    always @(*)					//��Ϊ������ʽ 
    begin
            if((sw_pin[0]==0 & sw_pin[1]==0) & (sw_pin[6]==0 & sw_pin[7]==0) | (sw_pin[0]==0 & sw_pin[1]==0) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==0 & sw_pin[1]==1) & (sw_pin[6]==0 & sw_pin[7]==1) | (sw_pin[0]==0 & sw_pin[1]==1) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==0) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==0 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==0 & sw_pin[7]==1) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==1 & sw_pin[7]==0) | (sw_pin[0]==1 & sw_pin[1]==1) & (sw_pin[6]==1 & sw_pin[7]==1)) 
                  		led_pin[0] <= 1;			    
            else
			led_pin[0] <= 0;
    end

endmodule