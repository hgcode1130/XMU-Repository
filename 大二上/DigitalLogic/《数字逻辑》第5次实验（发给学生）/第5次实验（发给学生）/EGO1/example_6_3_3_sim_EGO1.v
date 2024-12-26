//例题6.3的仿真程序。

`timescale 1ns / 1ps	

module example_6_3_3_sim();

    reg x1, x2;
    wire z;
    reg rd;
    reg y2, y1;
    wire ny2, ny1;
                               
    example_6_3_3 U(.x1(x1), .x2(x2), .y2(y2), .y1(y1), .rd(rd), .ny2(ny2), .ny1(ny1), .z(z));

    initial begin
         #0
         y2=0;
         y1=0;
         x1=0;
         x2=0;
         rd=0;

         #5000
         rd=1;

         #15000
         x1=1;
         x2=0;

         #20000
         x1=0;
         x2=0;

         #20000 
         x1=0;
         x2=1;

         #20000 
         x1=0;
         x2=0;

         #20000 
         x1=1;
         x2=0;

         #20000 
         x1=0;
         x2=0;

         #20000 
         x1=0;
         x2=1;

         #20000 
         x1=0;
         x2=0;

         #20000 
         x1=0;
         x2=1;

         #20000 
         x1=0;
         x2=0;

         #20000 
         x1=0;
         x2=1;

         #20000 
         x1=0;
         x2=0;

         #20000 
         x1=1;
         x2=0;

         #20000 
         x1=0;
         x2=0;
    end

    always #1 begin y2 <= ny2; y1 <= ny1; end
    
endmodule