//������Ϊ������ʽʵ������4.5����ֵ�Ƚ�����·������Ϊ������������ߵ�3���������غ����ұߵ�3���������أ����Ϊ������������ߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module example_4_5_1(
    input sw_pin[7:0],            	                   		 //8����������
    output reg [15:0] led_pin    		 	//16��led��            
);

    always @(*)					//��Ϊ������ʽ 
    begin
                if(sw_pin[0]==sw_pin[5] & sw_pin[1]==sw_pin[6] & sw_pin[2]==sw_pin[7])
                  		led_pin[0] <= 1;			    
                else
			led_pin[0] <= 0;
    end

endmodule