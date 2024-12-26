module clk_t_flip_flop_EGO1(
    input wire clk,
    input wire T,
    output wire Q,
    output wire Qn
);

    reg Q_reg;

    always @(posedge clk) begin
        if (T)
            Q_reg <= ~Q_reg;
        else
            Q_reg <= Q_reg;
    end

    assign Q = Q_reg;
    assign Qn = ~Q_reg;

endmodule