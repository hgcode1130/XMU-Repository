//����������������ʽʵ������4.9��ȫ����FA��·������Ϊ������������ߵ�3���������أ����Ϊ������������ߵ�2��LED�ơ�

`timescale 1ns / 1ps	

module example_4_9_2(
    input sw_pin[7:0],            	                   		 //8����������
    output [15:0] led_pin    		 		//16��led��            
);

    assign {led_pin[1], led_pin[0]} = sw_pin[0] + sw_pin[1] + sw_pin[2];  

endmodule