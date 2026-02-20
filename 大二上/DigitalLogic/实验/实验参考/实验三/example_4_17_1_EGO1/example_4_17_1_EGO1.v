module logic_circuit_pre_dataflow(
    input a,
    input b,
    input c,
    input d,
    output f_pre
);
 
assign f_pre = ~a & c | b & ~c & d | a & ~b & ~c;

endmodule

module top_module_pre_dataflow(
    input [7:0] sw_pin,   
    output [15:0] led_pin
);

logic_circuit_pre_dataflow uut(
 .a(sw_pin[0]),
 .b(sw_pin[1]),
 .c(sw_pin[2]),
 .d(sw_pin[3]),
 .f_pre(led_pin[0])
);

endmodule


module logic_circuit_post_dataflow(
    input a,
    input b,
    input c,
    input d,
    output f_post
);

assign f_post = ~a & c | b & ~c & d | a & ~b & ~c | ~a & b & d | a & ~c & d;

endmodule

module top_module_post_dataflow(
    input [7:0] sw_pin,   
    output [15:0] led_pin
);

logic_circuit_post_dataflow uut(
 .a(sw_pin[0]),
 .b(sw_pin[1]),
 .c(sw_pin[2]),
 .d(sw_pin[3]),
 .f_post(led_pin[7])
);

endmodule