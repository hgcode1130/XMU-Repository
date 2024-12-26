module exercise3_14_c(
    input wire CP,
    input wire A,
    input wire B,
    output reg Q
);

    wire T;
    assign T = A & B;

    always @(posedge CP) begin
        if (T)
            Q <= ~Q;
        else
            Q <= Q;
    end

endmodule