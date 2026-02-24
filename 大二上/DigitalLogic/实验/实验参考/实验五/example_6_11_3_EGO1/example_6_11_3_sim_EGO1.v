//例题6.11的仿真程序。
`timescale 1ns / 1ps
module example_6_11_3_sim();
    reg x1,x2;
    reg y2, y1;
    wire z, ny2, ny1;

    example_6_11_3 U(.x1(x1),.x2(x2), .y2(y2), .y1(y1), .ny2(ny2), .ny1(ny1), .z(z));
    initial begin
        #0
        y2=0;
        y1=0;
        
        x1=0;
        x2=0;
        #20
        x1=1;
        
        #60
        x1=0;
    end

    always #5 begin y2 <= ny2; y1 <= ny1; end
    always #10 begin x2 <= ~x2; end
endmodule