module half_adder_behavioral(
    input a_in,
    input b_in,
    output reg s_out,
    output reg c_out
);

always @(*) begin
    s_out = a_in ^ b_in;
    c_out = a_in & b_in;
end

endmodule

module top_module(
    input [1:0] switch,
    output [1:0] led
);

half_adder_behavioral uut(
   .a_in(switch[0]),
   .b_in(switch[1]),
   .s_out(led[0]),
   .c_out(led[1])
);

endmodule