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

module example_6_4(
    input x,
    input y1,y2,y3,
    output ny1,ny2,ny3,z
    );
    wire ny1n,ny2n,ny3n;
    
    t_flip_flop  U1(.cp(x),.t(1),.q(ny1),.qn(ny1n));
    t_flip_flop  U2(.cp(y1),.t(1),.q(ny2),.qn(ny2n));
    t_flip_flop  U3(.cp(y2),.t(1),.q(ny3),.qn(ny3n));
    and_gate U4(.a(x),.b(y1),.c(y2),.d(y3),.f(z));
    
endmodule    

module example_6_4_EGO1(
    input btn_1,
    output [15:0] led_pin
    );
    reg y1,y2,y3;
    example_6_4 U(.x(btn_1),.y1(y1),.y2(y2),.y3(y3),.ny1(led_pin[2]),.ny2(led_pin[1]),.ny3(led_pin[0]),.z(led_pin[7]));
    initial begin
        y3=0;
        y2=0;
        y1=0;
    end
    always @(*)                     		//行为描述方式
    begin
    y3 <= led_pin[0];
	y2 <= led_pin[1];
	y1 <= led_pin[2];
    end
    
endmodule
