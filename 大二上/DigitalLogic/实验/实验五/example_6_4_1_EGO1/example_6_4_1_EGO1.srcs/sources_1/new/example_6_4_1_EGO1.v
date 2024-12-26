`timescale 1ns / 1ps

module example_6_4_1(
    input x,
    input y1,y2,y3,
    output reg ny1,ny2,ny3,z
    );
    
    always @(negedge x)                      	//行为描述方式
    begin
                case({y3, y2, y1})
                0:begin ny3<=0;ny2<=0;ny1<=1;z<=0;end
                1:begin ny3<=0;ny2<=1;ny1<=0;z<=0;end
                2:begin ny3<=0;ny2<=1;ny1<=1;z<=0;end
                3:begin ny3<=1;ny2<=0;ny1<=0;z<=0;end
                4:begin ny3<=1;ny2<=0;ny1<=1;z<=0;end
                5:begin ny3<=1;ny2<=1;ny1<=0;z<=0;end
                6:begin ny3<=1;ny2<=1;ny1<=1;z<=0;end
                7:begin ny3<=0;ny2<=0;ny1<=0;z<=1;end
                endcase
    end

endmodule

module example_6_4_1_EGO1(
    input btn_1,				 //S1按钮
    output [15:0] led_pin
    );
    reg y3,y2,y1;
    
    example_6_4_1 U(.x(btn_1),.y1(y1),.y2(y2),.y3(y3),.ny1(led_pin[2]),.ny2(led_pin[1]),.ny3(led_pin[0]));
    
    initial begin
        y3=0;
        y2=0;
        y1=0;
    end

    always @(*)                     		//行为描述方式
    begin
    y3 <= led_pin[0];
	y2 <= led_pin[1];
	y1 <= led_pin[2];
    end
endmodule
