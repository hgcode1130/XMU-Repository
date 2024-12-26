//例题6.2的仿真程序。

`timescale 1ns / 1ps	

module example_6_2_3_sim();

    reg x1, x2, x3;
    reg y2, y1;
    wire z;
    reg rd; 
    wire ny2, ny1;
    reg y2n, y1n;
                               
    example_6_2_3 U(.x1(x1), .x2(x2), .x3(x3), .y2(y2), .y1(y1), .rd(rd), .ny2(ny2), .ny1(ny1), .z(z));

    initial begin
         #0
         y2=0;
         y2n=1;
         y1=0;
         y1n=1;
         x1=0;
         x2=0;
         x3=0;
         rd=0;

         #5000
         rd=1;

         #15000
         x1=1;

         #10000
         x1=0;

         #20000 
         x2=1;

         #10000 
         x2=0;

         #20000 
         x1=1;

         #10000 
         x1=0;

         #20000 
         x3=1;

         #10000 
         x3=0;

         #20000 
         x1=1;

         #10000 
         x1=0;

         #20000 
         x2=1;

         #10000 
         x2=0;

         #20000 
         x3=1;

         #10000 
         x3=0;

         #20000 
         x1=1;

         #10000 
         x1=0;

         #20000 
         x3=1;

         #10000 
         x3=0;

         #20000 
         x2=1;

         #10000 
         x2=0;
    end

    always #1 begin y2 <= ny2; y2n <= ~ny2; y1 <= ny1; y1n <= ~ny1; end
    
endmodule