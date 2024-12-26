`timescale 1ns / 1ps	

module and_gate(
    input a,b,
    output f
);
    reg y;
    always@(*)
    begin
        y<=a&b;
    end
    assign f=y;
endmodule

module carry_lookahead_adder(
    input a3, a2, a1, a0, b3, b2, b1, b0, cin,                         		 
    output f3, f2, f1 ,f0, cout    	
);

    reg y3, y2, y1, y0, c4, c3, c2, c1;

    always @(*)                        //行为描述方式
    begin
        {c1,y0} <= a0+b0+cin; 
        {c2,y1} <= a1+b1+c1; 
        {c3,y2} <= a2+b2+c2; 
        {c4,y3} <= a3+b3+c3; 
    end

    assign f0 = y0;
    assign f1 = y1;
    assign f2 = y2;
    assign f3 = y3;

    assign cout = c4;

endmodule

module multiplier_EGO1(
    input sw_pin[7:0],                               		 	//8个拨动开�?
    output [15:0] led_pin    		 		//16个led�?            
);
    wire f4,f3,f2,f1,fc1,f8,f7,f6,f5,fc2,y3,y2,y1,y0,x3,x2,x1,x0,a04,a03,a02,a01,b04,b03,b02,b01,a14,a13,a12,a11,b14,b13,b12,b12,b11;
    and_gate U1(.a(sw_pin[3]),.b(sw_pin[7]),.f(led_pin[7]));
    carry_lookahead_adder U2(.a3(sw_pin[6]&sw_pin[0]), .a2(sw_pin[1]&sw_pin[6]), .a1(sw_pin[2]&sw_pin[6]), .a0(sw_pin[3]&sw_pin[6]), .b3(0), .b2(sw_pin[0]&sw_pin[7]), .b1(sw_pin[1]&sw_pin[7]), .b0(sw_pin[2]&sw_pin[7]), .cin(0), .f3(f4), .f2(f3), .f1(f2), .f0(led_pin[6]), .cout(fc1));
    carry_lookahead_adder U3(.a3(sw_pin[0]&sw_pin[5]), .a2(sw_pin[1]&sw_pin[5]), .a1(sw_pin[2]&sw_pin[5]), .a0(sw_pin[3]&sw_pin[5]), .b3(fc1), .b2(f4), .b1(f3), .b0(f2), .cin(0), .f3(f8), .f2(f7), .f1(f6), .f0(led_pin[5]), .cout(fc2));
    carry_lookahead_adder U4(.a3(fc2), .a2(f8), .a1(f7), .a0(f6), .b3(sw_pin[0]&sw_pin[4]), .b2(sw_pin[1]&sw_pin[4]), .b1(sw_pin[2]&sw_pin[4]), .b0(sw_pin[3]&sw_pin[4]), .cin(0), .f3(led_pin[1]), .f2(led_pin[2]), .f1(led_pin[3]), .f0(led_pin[4]), .cout(led_pin[0]));
    
endmodule