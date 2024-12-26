//�ṹ��������ʽʵ������4.16������߼���·������������ǰ�����Լ�����������������߼���·������������󣩣�����Ϊ������������ߵ�3���������أ����Ϊ������������ߵ�LED�ƣ�����������ǰ�������ұߵ�LED�ƣ�����������ǰ����

`timescale 1ns / 1ps	

module not_gate(
    input a,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= ~a; 
    end
endmodule

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
        f <= ~(a & b & c); 
    end
endmodule

module example_4_16(
    input sw_pin[7:0],                               		 //8����������
    output [15:0] led_pin    		 	//16��led��            
);
    wire p1, p2, p3, p4, p5, p6, p7;

    nand2_gate U1(.a(sw_pin[1]),.b(sw_pin[0]),.f(p1));				//�ṹ��������ʽ
    not_gate U2(.a(sw_pin[0]),.f(p2));						//�ṹ��������ʽ
    nand2_gate U3(.a(p2),.b(sw_pin[2]),.f(p3));					//�ṹ��������ʽ
    nand2_gate U4(.a(p1),.b(p3),.f(led_pin[0]));					//�ṹ��������ʽ

    nand2_gate U5(.a(sw_pin[1]),.b(sw_pin[0]),.f(p4));				//�ṹ��������ʽ
    not_gate U6(.a(sw_pin[0]),.f(p5));						//�ṹ��������ʽ
    nand2_gate U7(.a(p5),.b(sw_pin[2]),.f(p6));					//�ṹ��������ʽ
    nand2_gate U8(.a(sw_pin[2]),.b(sw_pin[1]),.f(p7));				//�ṹ��������ʽ
    nand3_gate U9(.a(p4),.b(p6),.c(p7),.f(led_pin[7]));				//�ṹ��������ʽ

endmodule