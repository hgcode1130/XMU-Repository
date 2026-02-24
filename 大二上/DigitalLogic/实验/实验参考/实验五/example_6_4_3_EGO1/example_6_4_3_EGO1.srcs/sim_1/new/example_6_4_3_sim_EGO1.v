//示例6-4的仿真程序
`timescale 1ns / 1ps

module example_6_4_2_sim();
    reg y3 , y2, y1;
    reg x;
    wire z, ny3, ny2, ny1;
    example_6_4_2 U(.x(x), .y3(y3), .y2(y2), .y1(y1), .ny3(ny3), .ny2(ny2), .ny1(ny1), .z(z));
    
    initial begin
        #0
        y3=0;
        y2=0;
        y1=0;
        x=0;
        
        #10
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #20
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #30
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #20
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #30
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #30
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #30
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
        
        #30
        x=1;
        
        #5
        y3 = ny3;
        y2 = ny2;
        y1 = ny1;
        x=0;
    end
endmodule