module rs_flip_flop_1_EGO1(
    input wire S,
    input wire R,
    output wire Q,
    output wire Qn
);

    wire nS, nR;
    wire nQ, nQn;

    not_gate invS(S, nS);
    not_gate invR(R, nR);

    nor_gate nor1(nS, Qn, nQ);
    nor_gate nor2(nR, Q, nQn);

    assign Q = nQn;
    assign Qn = nQ;
    
    module not_gate(input wire in, output wire out);
        assign out = ~in;
    endmodule

    module nor_gate(input wire in1, input wire in2, output wire out);
        assign out = ~(in1 | in2);
    endmodule

endmodule