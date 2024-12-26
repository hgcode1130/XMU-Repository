//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������4.12Ѫ���Ƿ����ݵĵ�·������Ѫ�ͱ���I��������Ϊ������������ߵ�2���������غ����ұߵ�2�����أ����Ϊ������������ߵ�LED�ơ�

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

module nand4_gate(
    input a,
    input b,
    input c,
    input d,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= ~(a & b & c & d); 
    end
endmodule

module not_gate(
    input a,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= ~a; 
    end
endmodule

module example_4_12a(
    input sw_pin[7:0],                               		 //8����������
    output [15:0] led_pin    		 	//16��led��            
);
    wire p1, p2, p3, p4, p5, p6, p7, p8;

    not_gate U1(.a(sw_pin[0]),.f(p1));					//�ṹ��������ʽ
    not_gate U2(.a(sw_pin[1]),.f(p2));					//�ṹ��������ʽ
    not_gate U3(.a(sw_pin[7]),.f(p3));					//�ṹ��������ʽ
    not_gate U4(.a(sw_pin[6]),.f(p4));					//�ṹ��������ʽ

    nand3_gate U5(.a(p1),.b(p2),.c(p3),.f(p5));				//�ṹ��������ʽ
    nand2_gate U6(.a(sw_pin[6]),.b(p3),.f(p6));				//�ṹ��������ʽ
    nand2_gate U7(.a(sw_pin[0]),.b(sw_pin[1]),.f(p7));			//�ṹ��������ʽ
    nand3_gate U8(.a(p4),.b(sw_pin[1]),.c(sw_pin[7]),.f(p8));			//�ṹ��������ʽ

    nand4_gate U9(.a(p5),.b(p6),.c(p7),.d(p8),.f(led_pin[0]));			//�ṹ��������ʽ

endmodule