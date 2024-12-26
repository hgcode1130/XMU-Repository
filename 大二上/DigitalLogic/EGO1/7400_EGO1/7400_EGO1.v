//������������ʽʵ��4��2��������ţ�����Ϊ��ߵ�8���������أ����Ϊ��ߵ�LED���е�4����

`timescale 1ns / 1ps	

module ttl7400(
    input sw_pin[7:0],                                //8����������
    output [15:0] led_pin    		 //16��led��
);

    assign led_pin[0] = ~(sw_pin[0] & sw_pin[1]); 		//������������ʽ
    assign led_pin[2] = ~(sw_pin[2] & sw_pin[3]); 		//������������ʽ
    assign led_pin[4] = ~(sw_pin[4] & sw_pin[5]); 		//������������ʽ
    assign led_pin[6] = ~(sw_pin[6] & sw_pin[7]);		//������������ʽ

endmodule