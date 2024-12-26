//习题3.13的D触发器的仿真程序。

`timescale 1ns / 1ps	

module exercise_3_13_sim();
    reg cp, d;
    wire q, qn;
                               
    exercise_3_13 U(.cp(cp), .d(d), .q(q), .qn(qn));

    initial begin
         #0
         cp=0;
         d=1;
         
         #25 
         d=0;
         
         #20 
         d=1;
         
         #10 
         d=0;
         
         #20 
         d=1;
         
         #10 
         d=0;
    end
    
    always #10 cp = ~cp;

endmodule