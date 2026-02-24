`timescale 1ns / 1ps	

module example_6_4_2_sim();
    
    reg x;
    wire y3, y2, y1;  // 改为wire类型
    reg reset;
    wire z, ny3, ny2, ny1;
                               
    // 直接连接，让模块内部处理状态
    example_6_4_2 U(
        .x(x), 
        .reset(reset), 
        .y3(ny3),  // 直接连接
        .y2(ny2), 
        .y1(ny1), 
        .ny3(ny3), 
        .ny2(ny2), 
        .ny1(ny1), 
        .z(z)
    );

    // 将内部状态输出到外部观察
    assign y3 = ny3;
    assign y2 = ny2;
    assign y1 = ny1;

    initial begin
        #0
        x = 0;
        reset = 0;
        
        #500
        reset = 1;
        
        // 生成时钟
        repeat(16) begin
            #500 x=1;
            #500 x=0;
        end
    end
    
endmodule