//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������4.5�ıȽ�����3λ���������Ƿ���ȵ���ֵ�Ƚ�����·������Ϊ������������ߵ�3���������غ����ұߵ�3���������أ����Ϊ������������ߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module nor_gate(
    input a,
    input b,
    input c,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= ~(a | b | c); 
    end
endmodule

module xor_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= a ^ b; 
    end
endmodule

module example_4_5(
    input sw_pin[7:0],                               		 //8����������
    output [15:0] led_pin    		 	//16��led��            
);
    wire p1, p2, p3;

    xor_gate U1(.a(sw_pin[0]),.b(sw_pin[5]),.f(p1));				//�ṹ��������ʽ
    xor_gate U2(.a(sw_pin[1]),.b(sw_pin[6]),.f(p2));				//�ṹ��������ʽ
    xor_gate U3(.a(sw_pin[2]),.b(sw_pin[7]),.f(p3));				//�ṹ��������ʽ
    nor_gate U4(.a(p1),.b(p2),.c(p3),.f(led_pin[0]));				//�ṹ��������ʽ

endmodule