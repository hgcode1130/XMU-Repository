module half_adder_structural(
    input a_in,
    input b_in,
    output s_out,
    output c_out
);

// 内部信号声明
wire w1, w2, w3;

// 实例化逻辑门
and u1(w1, a_in, b_in);
xor u2(w2, a_in, b_in);
not u3(w3, w1);

// 连接输出
assign s_out = w2;
assign c_out = w1;

endmodule

module top_module(
    input [1:0] switch,
    output [1:0] led
);

half_adder_structural uut(
   .a_in(switch[0]),
   .b_in(switch[1]),
   .s_out(led[0]),
   .c_out(led[1])
);

endmodule