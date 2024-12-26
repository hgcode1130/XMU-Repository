`timescale 1ns / 1ps
module xor_gate(
    input a,
    input b,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a^b;
    end
    assign f=y;
endmodule    

module no_gate(
    input a,
    output f
);
    reg y;
    always@(*)
    begin
        y<= ~a;
    end
    assign f=y;
endmodule

module nand_gate1(
    input a,
    input b,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a&b;
    end
    assign f=~y;
endmodule  

module nand_gate(
    input a,
    input b,
    input c,
    output f
);
    reg y;
    always@(*)
    begin
        y<= a&b&c;
    end
    assign f=~y;
endmodule  

module d_gate(
    input cp,
    input d,
    output q
);
    reg y;
    always@(negedge cp)
    begin
            if(d==1)
                y<=1;
            else
                y<=0;       
    end
    assign q=y;
endmodule

module example_6_11(
    input x2,x1,
    input y2,y1,
    output ny2,ny1,z
    );
    wire f1,f2,f3,f4,f5,w1,w2;
    no_gate U1(.a(x2),.f(f1));
    no_gate U2(.a(x1),.f(f2));
    nand_gate U3(.a(f1),.b(f2),.c(y1),.f(f3));
    nand_gate1 U4(.a(x2),.b(y2),.f(f4));
    nand_gate1 U5(.a(y1),.b(f4),.f(f5));
    nand_gate1 U6(.a(f2),.b(f5),.f(w1));
    nand_gate1 U7(.a(f3),.b(f4),.f(w2));
    d_gate U8(.cp(1),.d(w1),.q(ny1));
    d_gate U9(.cp(1),.d(w2),.q(ny2));
    no_gate U10(.a(f4),.f(z));
endmodule

module example_6_11_EGO1(
    input btn_1,
    input sys_clk_in,                              		 	//8个拨动开关
    output [15:0] led_pin 
    );
    reg y2,y1;
    example_6_11 U(.x1(btn_1),.x2(sys_clk_in),.y2(y2),.y1(y1),.ny2(led_pin[0]),.ny1(led_pin[1]),.z(led_pin[7]));
    
    initial begin
        y2=0;
        y1=0;
    end
    always @(*)                     		//行为描述方式
    begin
	y2 <= led_pin[0];
	y1 <= led_pin[1];
    end
    
endmodule
