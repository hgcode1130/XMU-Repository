module logic_circuit_pre_dataflow(
    input a,
    input b,
    input c,
    input d,
    output f_pre
);

assign f_pre = a & c | b & ~c & d | a & ~b & ~c;

endmodule

module top_module_pre_dataflow(
    input [3:0] switches,
    output led_pre
);

logic_circuit_pre_dataflow uut(
 .a(switches[0]),
 .b(switches[1]),
 .c(switches[2]),
 .d(switches[3]),
 .f_pre(led_pre)
);

endmodule


module logic_circuit_post_dataflow(
    input a,
    input b,
    input c,
    input d,
    output f_post
);

assign f_post = a & c | b & ~c & d | a & ~b & ~c | a & b & d | a & ~c & d;

endmodule

module top_module_post_dataflow(
    input [3:0] switches,
    output led_post
);

logic_circuit_post_dataflow uut(
 .a(switches[0]),
 .b(switches[1]),
 .c(switches[2]),
 .d(switches[3]),
 .f_post(led_post)
);

endmodule