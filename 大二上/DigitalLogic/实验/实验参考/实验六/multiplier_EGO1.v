//采用结构化描述方式实现4位二进制乘法器
`timescale 1ns / 1ps	
module full_adder(
    input a,
    input b,
    input cin,
    output f,
    output cout                               
);
    reg y1, y2;

    always @(*)                        //行为描述方式
    begin
        {y2,y1} <= a+b+cin; 
    end

    assign f = y1;
    assign cout = y2;

endmodule

module ttl74283(
    input a4,a3,a2,a1,b4,b3,b2,b1,c0,                    		 
    output  f4,f3,f2,f1,fc4   	
);
    wire c1, c2, c3;

    // Full adder for bit 1
    full_adder fa1 (
        .a(a1), 
        .b(b1), 
        .cin(c0), 
        .f(f1), 
        .cout(c1)
    );


    // Full adder for bit 2
    full_adder fa2 (
        .a(a2), 
        .b(b2), 
        .cin(c1), 
        .f(f2), 
        .cout(c2)
    );

    // Full adder for bit 3
       full_adder fa3 (
        .a(a3), 
        .b(b3), 
        .cin(c2), 
        .f(f3), 
        .cout(c3)
    );

 // Full adder for bit 4
    full_adder fa4 (
        .a(a4), 
        .b(b4), 
        .cin(c3), 
        .f(f4), 
        .cout(fc4)
    );
endmodule

module and_gate(
    input a,
    input b,
    output reg f                               
);
    always @(*)                        //行为描述方式
    begin
        f <= a & b; 
    end
endmodule


module multiplier(
	input y3,y2,y1,y0,x3,x2,x1,x0,
	output z7,z6,z5,z4,z3,z2,z1,z0
);
    wire a14,a13,a12,a11,b13,b12,b11,a24,a23,a22,a21,b34,b33,b32,b31;
    wire f14,f13,f12,fc41;
    wire f24,f23,f22,fc42;
    and_gate U1(.a(y1),.b(x3),.f(a14));
    and_gate U2(.a(y1),.b(x2),.f(a13));
    and_gate U3(.a(y1),.b(x1),.f(a12));
    and_gate U4(.a(y1),.b(x0),.f(a11));
    and_gate U5(.a(y0),.b(x3),.f(b13));
    and_gate U6(.a(y0),.b(x2),.f(b12));
    and_gate U7(.a(y0),.b(x1),.f(b11));
    and_gate U8(.a(y0),.b(x0),.f(z0));   
    ttl74283 U9(.a4(a14),.a3(a13),.a2(a12),.a1(a11),.b4(0),.b3(b13),.b2(b12),.b1(b11),.c0(0),.f4(f14),.f3(f13),.f2(f12),.f1(z1),.fc4(fc41));
    and_gate U10(.a(y2),.b(x3),.f(a24));
    and_gate U11(.a(y2),.b(x2),.f(a23));
    and_gate U12(.a(y2),.b(x1),.f(a22));
    and_gate U13(.a(y2),.b(x0),.f(a21));
    ttl74283 U14(.a4(a24),.a3(a23),.a2(a22),.a1(a21),.b4(fc41),.b3(f14),.b2(f13),.b1(f12),.c0(0),.f4(f24),.f3(f23),.f2(f22),.f1(z2),.fc4(fc42));
    and_gate U15(.a(y3),.b(x3),.f(b34));
    and_gate U16(.a(y3),.b(x2),.f(b33));
    and_gate U17(.a(y3),.b(x1),.f(b32));
    and_gate U18(.a(y3),.b(x0),.f(b31));
    ttl74283 U19(.a4(fc42),.a3(f24),.a2(f23),.a1(f22),.b4(b34),.b3(b33),.b2(b32),.b1(b31),.c0(0),.f4(z6),.f3(z5),.f2(z4),.f1(z3),.fc4(z7));
endmodule

module multiplier_exe(
    input sw_pin[7:0],
    output led_pin[15:0]
);
    multiplier U(.y3(sw_pin[0]),.y2(sw_pin[1]),.y1(sw_pin[2]),.y0(sw_pin[3]),.x3(sw_pin[4]),.x2(sw_pin[5]),.x1(sw_pin[6]),.x0(sw_pin[7]),.z7(led_pin[0]),.z6(led_pin[1]),.z5(led_pin[2]),.z4(led_pin[3]),.z3(led_pin[4]),.z2(led_pin[5]),.z1(led_pin[6]),.z0(led_pin[7]));
endmodule