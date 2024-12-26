`timescale 1ns / 1ps


module example_5_4_1_EGO1(
    input sw_pin [0:7],
    input btn_1,
    output reg [15:0] led_pin
    );
    always @(negedge btn_1)                      //行为描述方式

    begin
                case({sw_pin[0], led_pin[0], led_pin[1], led_pin[2]})
                    0:begin led_pin[0] <= 0; led_pin[1] <= 0; led_pin[2] <= 0; led_pin[7] <= 0;end
                    1:begin led_pin[0] <= 0; led_pin[1] <= 1; led_pin[2] <= 0; led_pin[7] <= 1;end
                    2:begin led_pin[0] <= 1; led_pin[1] <= 0; led_pin[2] <= 0; led_pin[7] <= 1;end
                    3:begin led_pin[0] <= 1; led_pin[1] <= 1; led_pin[2] <= 0; led_pin[7] <= 0;end
                    4:begin led_pin[0] <= 0; led_pin[1] <= 0; led_pin[2] <= 0; led_pin[7] <= 1;end
                    5:begin led_pin[0] <= 0; led_pin[1] <= 1; led_pin[2] <= 0; led_pin[7] <= 0;end
                    6:begin led_pin[0] <= 1; led_pin[1] <= 0; led_pin[2] <= 0; led_pin[7] <= 0;end
                    7:begin led_pin[0] <= 1; led_pin[1] <= 1; led_pin[2] <= 0; led_pin[7] <= 1;end
                    
                    8:begin led_pin[0] <= 0; led_pin[1] <= 0; led_pin[2] <= 1; led_pin[7] <= 0;end
                    9:begin led_pin[0] <= 0; led_pin[1] <= 1; led_pin[2] <= 1; led_pin[7] <= 1;end
                    10:begin led_pin[0] <= 1; led_pin[1] <= 0; led_pin[2] <= 1; led_pin[7] <= 1;end
                    11:begin led_pin[0] <= 1; led_pin[1] <= 1; led_pin[2] <= 1; led_pin[7] <= 0;end
                    12:begin led_pin[0] <= 0; led_pin[1] <= 0; led_pin[2] <= 1; led_pin[7] <= 1;end
                    13:begin led_pin[0] <= 0; led_pin[1] <= 1; led_pin[2] <= 1; led_pin[7] <= 0;end
                    14:begin led_pin[0] <= 1; led_pin[1] <= 0; led_pin[2] <= 1; led_pin[7] <= 0;end
                    15:begin led_pin[0] <= 1; led_pin[1] <= 1; led_pin[2] <= 1; led_pin[7] <= 1;end                   
                endcase
    end                
endmodule
