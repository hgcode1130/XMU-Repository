//����������������ʽʵ������4.16������߼���·������������ǰ�����Լ�����������������߼���·������������󣩣�����Ϊ������������ߵ�3���������أ����Ϊ������������ߵ�LED�ƣ�����������ǰ�������ұߵ�LED�ƣ�����������ǰ����

`timescale 1ns / 1ps	

module example_4_16_1(
    input sw_pin[7:0],            	                   		 //8����������
    output [15:0] led_pin    		 		//16��led��            
);

    assign led_pin[0] = (sw_pin[0] & sw_pin[1]) | (~sw_pin[0] & sw_pin[2]);  

    assign led_pin[7] = (sw_pin[0] & sw_pin[1]) | (~sw_pin[0] & sw_pin[2]) | (sw_pin[1] & sw_pin[2]);  

endmodule