module half_adder_behavioral(
    input a_in,
    input b_in,
    output reg s_out,
    output reg c_out
);

always @(*) 
begin
//行为描述方式
    case({a_in, b_in})
        0: begin s_out <= 0;c_out<= 0; end
        1: begin s_out <= 1;c_out<= 0; end
        2: begin s_out <= 1;c_out<= 0; end
        3: begin s_out <= 0;c_out<= 1; end
    endcase
end

endmodule

module top_module(
    nput [7:0] sw_pin,
    output [15:0] led_pin  
);

half_adder_behavioral uut(
   .a_in(sw_pin[0]),
   .b_in(sw_pin[1]),
   .s_out(led_pin[0]),
   .c_out(led_pin[1])
);

endmodule