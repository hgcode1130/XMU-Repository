//例题6.1的仿真程序。

`timescale 1ns / 1ps	

module example_6_1_3_sim();

    reg x;
    reg y2, y1;
    wire z;
    reg rd;
    wire ny2, ny1;

    example_6_1_3 U(.x(x), .y2(y2), .y1(y1), .rd(rd), .ny2(ny2), .ny1(ny1), .z(z));

    initial begin
         #0
         y2=0;
         y1=0;
         x=0;
         rd=0;

         #5000
         rd=1;

         #5000
         x=1;

         #5000
         x=0;

         #20000 
         x=1;

         #5000 
         x=0;

         #30000 
         x=1;

         #5000 
         x=0;

         #20000 
         x=1;

         #5000 
         x=0;

         #40000 
         x=1;

         #5000 
         x=0;
    end

    always #1 begin y2 <= ny2; y1 <= ny1; end
    
endmodule