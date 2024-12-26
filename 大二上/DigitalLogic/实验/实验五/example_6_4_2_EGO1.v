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

module one_gate(
    input a,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a;
    end
    assign f=y;
endmodule

module and_gate(
    input a,
    input b,
    input c,
    input d,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a&b&c&d;
    end
    assign f=y;
endmodule   

module t_flip_flop(
    input cp,
    input t,
    output q,qn
);
    reg y;
    always@(negedge cp)
    begin
            if(t==1)
                y<=~y;
            else
                y<=y;       
    end
    assign q=y;
    assign qn=~y;
endmodule

module example_6_4_2(
    input x,
    input y1,y2,y3,
    input rd,
    output ny1,ny2,ny3,z
    );
    wire ny1n,ny2n,ny3n;
    
    t_flip_flop  U1(.cp(x),.t(1),.q(ny1),.qn(ny1n));
    t_flip_flop  U2(.cp(y1),.t(1),.q(ny2),.qn(ny2n));
    t_flip_flop  U3(.cp(y2),.t(1),.q(ny3),.qn(ny3n));
    and_gate U4(.a(x),.b(y1),.c(y2),.d(y3),.f(z));
    
endmodule   