module clk_d_flip_flop_EGO1(
    input wire clk,
    input wire D,
    output wire Q,
    output wire Qn
);

    reg Q_reg;

    always @(posedge clk) begin
        Q_reg <= D;
    end

    assign Q = Q_reg;
    assign Qn = ~Q_reg;

endmodule