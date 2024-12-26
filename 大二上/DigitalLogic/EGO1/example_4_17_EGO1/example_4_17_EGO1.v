module logic_circuit_pre(
    input a,
    input b,
    input c,
    input d,
    output f_pre
);

// 内部信号声明
wire w1, w2, w3;

// 实例化逻辑门
and u1(w1, a, c);
and u2(w2, b, not(c), d);
and u3(w3, a, not(b), not(c));
or u4(f_pre, w1, w2, w3);

endmodule

module top_module_pre(
    input [3:0] switches,
    output led_pre
);

logic_circuit_pre uut(
 .a(switches[0]),
 .b(switches[1]),
 .c(switches[2]),
 .d(switches[3]),
 .f_pre(led_pre)
);

endmodule

module logic_circuit_post(
    input a,
    input b,
    input c,
    input d,
    output f_post
);

// 内部信号声明
wire w1, w2, w3, w4, w5;

// 实例化逻辑门
and u1(w1, a, c);
and u2(w2, b, not(c), d);
and u3(w3, a, not(b), not(c));
and u4(w4, a, b, d);
and u5(w5, a, not(c), d);
or u6(f_post, w1, w2, w3, w4, w5);

endmodule

module top_module_post(
    input [3:0] switches,
    output led_post
);

logic_circuit_post uut(
 .a(switches[0]),
 .b(switches[1]),
 .c(switches[2]),
 .d(switches[3]),
 .f_post(led_post)
);

endmodule