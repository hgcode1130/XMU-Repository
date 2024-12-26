//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������4.3�Ĳ�һ�µ�·������Ϊ����ߵ�4���������أ����Ϊ����ߵ�4��LED�ơ�

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

module or_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= a | b; 
    end
endmodule

module and_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //��Ϊ������ʽ
    begin
        f <= a & b; 
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

module example_4_3(
    input sw_pin[7:0],                               		 //8����������
    output [15:0] led_pin    		 	//16��led��            
);
    wire p1, p2;

    or_gate U1(.a(sw_pin[2]),.b(sw_pin[3]),.f(p1));				//�ṹ��������ʽ
    and_gate U2(.a(sw_pin[1]),.b(p1),.f(p2));				//�ṹ��������ʽ
    xor_gate U3(.a(sw_pin[0]),.b(p2),.f(led_pin[0]));				//�ṹ��������ʽ
    xor_gate U4(.a(p1),.b(sw_pin[1]),.f(led_pin[1]));				//�ṹ��������ʽ
    not_gate U5(.a(sw_pin[3]),.f(led_pin[3]));				//�ṹ��������ʽ
    xor_gate U6(.a(sw_pin[2]),.b(led_pin[3]),.f(led_pin[2]));			//�ṹ��������ʽ

endmodule