//�ṹ��������ʽʵ��4��2��������ţ�����Ϊ��ߵ�8���������أ����Ϊ��ߵ�LED���е�4����

`timescale 1ns / 1ps	

module nandgate(
    input a,
    input b,
    output f
);

    assign f = ~(a & b); 	//������������ʽ

endmodule

module ttl7400_2(
    input sw_pin[7:0],                               		 //8����������
    output [15:0] led_pin    		 	//16��led��
);

    nandgate U1(.a(sw_pin[0]),.b(sw_pin[1]),.f(led_pin[0]));		//�ṹ��������ʽ
    nandgate U2(.a(sw_pin[2]),.b(sw_pin[3]),.f(led_pin[2]));		//�ṹ��������ʽ
    nandgate U3(.a(sw_pin[4]),.b(sw_pin[5]),.f(led_pin[4]));		//�ṹ��������ʽ
    nandgate U4(.a(sw_pin[6]),.b(sw_pin[7]),.f(led_pin[6]));		//�ṹ��������ʽ

endmodule