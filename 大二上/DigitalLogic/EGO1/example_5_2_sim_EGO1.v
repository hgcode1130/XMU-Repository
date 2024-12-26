//例题5.2的仿真程序。

`timescale 1ns / 1ps	

module example_5_2_sim();

    reg cp, x;
    wire ny2, ny1;
    wire z;

    reg rd;
    wire ny2n, ny1n;
    reg y2, y1;
    reg y2n, y1n;
                               
    example_5_2 U(.cp(cp), .x(x), .rd(rd), .y2(y2), .y2n(y2n), .y1(y1), .y1n(y1n), .ny2(ny2), .ny2n(ny2n), .ny1(ny1), .ny1n(ny1n), .z(z));

    initial begin
         #0
         cp=0;
         rd=0;
         x=0;

         #5
         rd=1;

         #20     
         x=1;

         #20
         x=0;

         #20 
         x=1;

         #20 
         x=1;

         #20 
         x=0;

         #20 
         x=1;

         #20 
         x=0;

         #20 
         x=0;
    end
    
    always #10 cp <= ~cp;

    always #20 begin y2 <= ny2; y2n <= ny2n; y1 <= ny1; y1n <= ny1n; end

endmodule