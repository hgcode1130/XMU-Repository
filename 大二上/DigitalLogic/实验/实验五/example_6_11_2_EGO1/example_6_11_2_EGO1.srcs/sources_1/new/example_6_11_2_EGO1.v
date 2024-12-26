`timescale 1ns / 1ps
module xor_gate(
    input a,
    input b,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a^b;
    end
    assign f=y;
endmodule    

module no_gate(
    input a,
    output f
);
    reg y;
    always@(*)
    begin
        y<= ~a;
    end
    assign f=y;
endmodule

module nand_gate1(
    input a,
    input b,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a&b;
    end
    assign f=~y;
endmodule  

module nand_gate(
    input a,
    input b,
    input c,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a&b&c;
    end
    assign f=~y;
endmodule  

module example_6_11_2(
    input x2,x1,
    input y2,y1,
    output ny2,ny1,z
    );
    wire f1,f2,f3,f4,f5;
    no_gate U1(.a(x2),.f(f1));
    no_gate U2(.a(x1),.f(f2));
    nand_gate U3(.a(f1),.b(f2),.c(y1),.f(f3));
    nand_gate1 U4(.a(x2),.b(y2),.f(f4));
    nand_gate1 U5(.a(y1),.b(f4),.f(f5));
    nand_gate1 U6(.a(f2),.b(f5),.f(ny1));
    nand_gate1 U7(.a(f3),.b(f4),.f(ny2));
    no_gate U8(.a(f4),.f(z));
endmodule
