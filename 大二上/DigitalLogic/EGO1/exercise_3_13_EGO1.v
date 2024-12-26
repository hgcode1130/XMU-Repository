//结构化描述方式（子模块采用行为描述方式）实现习题3.13的D触发器，输入为D和CP，输出为Q和/Q。

`timescale 1ns / 1ps	

module not_gate(
    input a,
    output reg f                               
);

    always @(*)                        //行为描述方式
    begin
        f <= ~a; 
    end

endmodule

module nand_gate(
    input a,
    input b,
    output reg f                               
);

    always @(*)                        //行为描述方式
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

    not_gate U1(.a(d),.f(f1));			//结构化描述方式
    nand_gate U2(.a(d),.b(cp),.f(f2));		//结构化描述方式
    nand_gate U3(.a(f1),.b(cp),.f(f3));		//结构化描述方式
    nand_gate U4(.a(f2),.b(qn),.f(q));		//结构化描述方式
    nand_gate U5(.a(f3),.b(q),.f(qn));		//结构化描述方式

endmodule