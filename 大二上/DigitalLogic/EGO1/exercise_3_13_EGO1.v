//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ��ϰ��3.13��D������������ΪD��CP�����ΪQ��/Q��

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

module nand_gate(
    input a,
    input b,
    output reg f                               
);

    always @(*)                        //��Ϊ������ʽ
    begin
        f <= ~(a & b); 
    end

endmodule

module exercise_3_13(
    input cp,
    input d,
    output q,
    output qn                               
);

    wire f1, f2, f3;

    not_gate U1(.a(d),.f(f1));			//�ṹ��������ʽ
    nand_gate U2(.a(d),.b(cp),.f(f2));		//�ṹ��������ʽ
    nand_gate U3(.a(f1),.b(cp),.f(f3));		//�ṹ��������ʽ
    nand_gate U4(.a(f2),.b(qn),.f(q));		//�ṹ��������ʽ
    nand_gate U5(.a(f3),.b(q),.f(qn));		//�ṹ��������ʽ

endmodule