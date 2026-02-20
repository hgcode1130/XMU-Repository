//采用行为描述方式实现例6-11的单脉冲发生器，输入x2接开发板的S1按键（ACE1开发板为KEY1按键）
//状态（y2, y1）和输出Z分别开发板上最左边的2个LED以及最右边的LED灯。
`timescale 1ns / 1ps
module example_6_11_3 (
    input x2, x1,
    input y2, y1,
    output reg ny2, ny1, z
);
    always @(*)        //行为描述方式
    begin
        if(x2==0 && x1==0) begin
            case({y2, y1})
                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end
                1: begin ny2 <= 1; ny1 <= 1; z <= 0; end
                2: begin ny2 <= 1; ny1 <= 1; z <= 0; end
                3: begin ny2 <= 0; ny1 <= 0; z <= 0; end
            endcase
        end

        if(x2==0 && x1==1) begin
            case({y2, y1})
                0: begin ny2 <= 0; ny1 <= 1; z <= 0; end
                1: begin ny2 <= 0; ny1 <= 1; z <= 0; end
                2: begin ny2 <= 0; ny1 <= 0; z <= 0; end
                3: begin ny2 <= 0; ny1 <= 0; z <= 0; end
            endcase
        end

        if(x2==1 && x1==1) begin
            case({y2, y1})
                0: begin ny2 <= 0; ny1 <= 1; z <= 0; end
                1: begin ny2 <= 0; ny1 <= 1; z <= 0; end
                3: begin ny2 <= 0; ny1 <= 0; z <= 0; end
                2: begin ny2 <= 0; ny1 <= 0; z <= 0; end
            endcase
        end

        if(x2==1 && x1==0) begin
            case({y2, y1})
                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end
                1: begin ny2 <= 0; ny1 <= 1; z <= 0; end
                3: begin ny2 <= 1; ny1 <= 0; z <= 0; end
                2: begin ny2 <= 1; ny1 <= 0; z <= 1; end
            endcase
        end
    end
endmodule

module example_6_11_1(
    input btn_1,
    input clk,
    output [7:0] led_pin     ////8个LED灯
);
reg y2, y1;

example_6_11_3 U(.x2(clk), .x1(btn_1), .y2(y2), .y1(y1), .ny2(led_pin[7]), .ny1(led_pin[6]), .z(led_pin[0]));
    initial begin
        y2 = 0;
        y1 = 0;
    end
    
    always @(*)        //行为描述方式
    begin
        y2 <= led_pin[7];
        y1 <= led_pin[6];
    end
endmodule