module exercise3_14_b(
    input wire CP,
    input wire A,
    input wire B,
    output reg Q
);

    wire D;
    assign D = ~(A ^ B);

    always @(posedge CP) begin
        Q <= D;
    end

endmodule