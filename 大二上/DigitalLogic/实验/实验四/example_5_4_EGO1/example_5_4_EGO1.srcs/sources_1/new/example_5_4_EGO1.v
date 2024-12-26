`timescale 1ns / 1ps

module one_gate(
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

module example_5_4_EGO1(
    input sw_pin [0:7],
    input btn_1,
    output [15:0] led_pin
    );
    wire y1, y2, y3, y1n, y2n, y3n, t1, t2, t3, f1;
    one_gate U1(.a(sw_pin[0]),.b(y1),.f(t1));
    one_gate U2(.a(y1),.b(y2),.f(t2));
    one_gate U3(.a(y2),.b(y3),.f(t3));
    t_flip_flop U4(.cp(btn_1),.t(t1),.q(y1),.qn(y1n));
    t_flip_flop U5(.cp(btn_1),.t(t2),.q(y2),.qn(y2n));
    t_flip_flop U6(.cp(btn_1),.t(t3),.q(y3),.qn(y3n));
    one_gate U7(.a(y3),.b(y2),.f(f1));
    one_gate U8(.a(f1),.b(y1),.f(led_pin[7]));
    assign led_pin[0] = y3;
    assign led_pin[1] = y2;
    assign led_pin[2] = y1;
endmodule
