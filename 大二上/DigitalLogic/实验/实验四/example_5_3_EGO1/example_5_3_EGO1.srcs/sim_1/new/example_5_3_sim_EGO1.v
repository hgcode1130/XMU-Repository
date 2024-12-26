
`timescale 1ns / 1ps	

module example_5_3_sim();

    reg cp, x1, x2;
    wire ny ;
    wire z;

    reg rd;
    wire nyn;
    reg y;
    reg yn;
                               
    example_5_3 U(.cp(cp), .x1(x1),.x2(x2), .rd(rd), .y(y), .yn(yn),.ny(ny), .nyn(nyn), .z(z));

    initial begin
         #0
         cp=0;
         rd=0;
         x1=0;
         x2=0;

         #5
         rd=1;

         #20     
         x1=0;
         x2=1;

         #20
         x1=1;
         x2=0;

         #20 
         x1=1;
         x2=1;

         #20 
         x1=0;
         x2=1;

         #20 
         x1=1;
         x2=1;

         #20 
         x1=1;
         x2=0;

         #20 
         x1=0;
         x2=0;

         #20 
         x1=0;
    end
    
    always #10 cp <= ~cp;

    always #20 begin y <= ny; yn <= nyn; end

endmodule
