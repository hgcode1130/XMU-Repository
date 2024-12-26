`timescale 1ns/1ns

module exercise3_14_tb;

    reg CP;
    reg A;
    reg B;
    wire Q_b;
    wire Q_c;

    exercise3_14_b uut_b(
       .CP(CP),
       .A(A),
       .B(B),
       .Q(Q_b)
    );

    exercise3_14_c uut_c(
       .CP(CP),
       .A(A),
       .B(B),
       .Q(Q_c)
    );

    initial begin
        CP = 0;
        A = 0;
        B = 0;
        #10;
        A = 0;
        B = 1;
        #10;
        A = 1;
        B = 0;
        #10;
        A = 1;
        B = 1;
        #10;
        A = 0;
        B = 0;
        #10;
        $finish;
    end

    always #5 CP = ~CP;

endmodule