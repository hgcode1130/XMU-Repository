//例题5.2的仿真程序。

`timescale 1ns / 1ps	

module example_5_2_1_sim();

    reg cp, x;
    wire ny2, ny1, z;

    reg rd;
    reg y2, y1;
                               
    example_5_2_1 U(.cp(cp), .x(x), .rd(rd), .y2(y2), .y1(y1), .ny2(ny2), .ny1(ny1), .z(z));

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

    always #20 begin y2 <= ny2; y1 <= ny1; end

endmodule