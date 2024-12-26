module orgate_EGO1(
    input wire sw1, sw2,
    output wire led
);

    assign led = sw1 | sw2;

endmodule