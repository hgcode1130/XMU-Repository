module notgate_EGO1(
    input wire in_switch,
    output wire led
);

    reg out;

    always @(*) begin
        out = ~in_switch;
    end

    assign led = out;

endmodule