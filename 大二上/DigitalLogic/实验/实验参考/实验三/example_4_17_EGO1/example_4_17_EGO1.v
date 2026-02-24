`timescale 1ns/1ps
module example_4_17(
    input [7:0] sw_pin,   
    output [15:0] led_pin 
);
    wire w1,w2,w3,w4,w5,w6,w7,w8;
    not u1(w1,sw_pin[0]);
    not u2(w2,sw_pin[1]);
    not u3(w3,sw_pin[2]);
    
    and u4(w4,w1,sw_pin[2]);
    and u5(w5,sw_pin[1],sw_pin[3],w3);
    and u6(w6,sw_pin[0],w2.w3);
    
    and u7(w7,w1,sw_pin[1],sw_pin[3]);
    and u8(w8,sw_pin[0],sw_pin[3],w3);
    
    or u9(led_pin[0],w4,w5,w6);
    or u10(led_pin[7],w4,w5,w6,w7,w8);
endmodule