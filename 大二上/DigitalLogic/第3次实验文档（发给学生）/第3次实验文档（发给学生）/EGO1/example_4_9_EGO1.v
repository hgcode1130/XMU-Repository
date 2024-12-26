//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������4.9��ȫ������·������Ϊ������������ߵ�3���������أ����Ϊ������������ߵ�2��LED�ƣ���·I�������ұߵ�2��LED�ƣ���·II����

`timescale 1ns / 1ps	

module nand2_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= ~(a & b); 
    end
endmodule

module nand3_gate(
    input a,
    input b,
    input c,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= ~(a & b &c); 
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

module example_4_9(
    input sw_pin[7:0],                               		 //8����������
    output [15:0] led_pin    		 	//16��led��            
);
    wire p1, p2, p3, p4, p5, p6, p7;

    xor_gate U1(.a(sw_pin[0]),.b(sw_pin[1]),.f(p1));					//�ṹ��������ʽ
    nand2_gate U2(.a(sw_pin[0]),.b(sw_pin[1]),.f(p2));				//�ṹ��������ʽ
    nand2_gate U3(.a(sw_pin[0]),.b(sw_pin[2]),.f(p3));				//�ṹ��������ʽ
    nand2_gate U4(.a(sw_pin[1]),.b(sw_pin[2]),.f(p4));				//�ṹ��������ʽ
    xor_gate U5(.a(p1),.b(sw_pin[2]),.f(led_pin[0]));					//�ṹ��������ʽ
    nand3_gate U6(.a(p2),.b(p3),.c(p4),.f(led_pin[1]));				//�ṹ��������ʽ

    xor_gate U7(.a(sw_pin[0]),.b(sw_pin[1]),.f(p5));					//�ṹ��������ʽ
    nand2_gate U8(.a(p5),.b(sw_pin[2]),.f(p6));					//�ṹ��������ʽ
    nand2_gate U9(.a(sw_pin[0]),.b(sw_pin[1]),.f(p7));				//�ṹ��������ʽ
    xor_gate U10(.a(p5),.b(sw_pin[2]),.f(led_pin[6]));				//�ṹ��������ʽ
    nand2_gate U11(.a(p6),.b(p7),.f(led_pin[7]));					//�ṹ��������ʽ

endmodule