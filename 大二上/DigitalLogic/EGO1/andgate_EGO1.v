//������������ʽʵ��2�������ţ�2������Ϊ����ߵ�2���������أ����Ϊ����ߵ�LED��

`timescale 1ns / 1ps	

module andgate(
    input sw_pin[7:0],                               //8����������
    output [15:0] led_pin    		//16��led��
);

    assign led_pin[0] = sw_pin[0] & sw_pin[1]; 		//������������ʽ

endmodule