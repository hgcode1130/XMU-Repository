//例题5.3的仿真程序。

`timescale 1ns / 1ps	

module example_5_3_sim();

    reg cp, x1,x2;
    wire ny1, z;
    wire ny1n;
    reg y1, y1n;
                               
    example_5_3 U(.cp(cp), .x1(x1), .x2(x2), .y1(y1), .y1n(y1n), .ny1(ny1), .ny1n(ny1n), .z(z));

    initial begin
         #0
         y1=0;
         y1n=1;
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

    always #20 begin y1 <= ny1; y1n <= ny1n; end

endmodule