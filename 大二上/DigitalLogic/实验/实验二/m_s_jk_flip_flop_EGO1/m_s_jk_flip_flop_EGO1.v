module m_s_jk_flip_flop_EGO1(
    input wire clk,
    input wire J,
    input wire K,
    output wire Q,
    output wire Qn
);

    reg master_Q;
    reg slave_Q;

    always @(posedge clk) begin
        // Master flip-flop
        master_Q <= (J & ~master_Q) | (~K & master_Q);
    end

    always @(negedge clk) begin
        // Slave flip-flop
        slave_Q <= master_Q;
    end

    assign Q = slave_Q;
    assign Qn = ~slave_Q;

endmodule