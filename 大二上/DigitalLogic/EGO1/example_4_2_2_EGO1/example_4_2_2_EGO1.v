module half_adder_dataflow(
    input a_in,
    input b_in,
    output s_out,
    output c_out
);

assign s_out = a_in ^ b_in;
assign c_out = a_in & b_in;

endmodule

module top_module(
    input [1:0] switch,
    output [1:0] led
);

half_adder_dataflow uut(
   .a_in(switch[0]),
   .b_in(switch[1]),
   .s_out(led[0]),
   .c_out(led[1])
);

endmodule