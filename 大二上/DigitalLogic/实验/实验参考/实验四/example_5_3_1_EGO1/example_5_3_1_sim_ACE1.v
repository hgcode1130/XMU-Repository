//例题5.3的仿真程序。

`timescale 1ns / 1ps	

module example_5_3_1_sim();

    reg cp, x1,x2;
    wire ny1, z;
    reg y1;
                               
    example_5_3_1 U(.cp(cp), .x1(x1), .x2(x2), .y1(y1), .ny1(ny1), .z(z));

    initial begin
         #0
         y1=0;
         cp=1;
         x1=0;
		 x2=0;
		 #20
		 x2=1;
         #20          
         x1=1;
		 x2=0;
         #20
         x2=1;
         #20 
         x1=0;
         #20 
         x1=1;
         #20 
         x2=0;
         #20 
         x1=0;
    end
    
    always #10 cp <= ~cp;

    always #20 begin y1 <= ny1; end

endmodule