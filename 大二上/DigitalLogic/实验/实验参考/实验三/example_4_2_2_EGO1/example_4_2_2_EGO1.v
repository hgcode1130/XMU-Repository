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
    input [7:0] sw_pin,   
    output [15:0] led_pin    	
);

half_adder_dataflow uut(
   .a_in(sw_pin[0]),
   .b_in(sw_pin[1]),
   .s_out(led_pin[0]),
   .c_out(led_pin[1])
);

endmodule