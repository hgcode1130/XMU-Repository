//结构化描述方式（子模块采用行为描述方式）实现例题5.1的2位二进制数可逆计数器，开发板上的输入（x、CP）为开发板上最左边的拨动开关以及S1按键，输出（y2、y1）为开发板上最左边的2个LED灯。

`timescale 1ns / 1ps	

module xor_gate(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= a ^ b; 
    end
    assign f = y;
endmodule

module jk_flip_flop(
    input j, k,                               	  
    input cp,                                                         
    output q, qn		
);
    reg y;
    always @(negedge cp)                     //行为描述方式
    begin
                case({j,k})
	               1: y <= 0;			      //  JK  =  01       Y=0
	               2: y <= 1;			      //  JK  =  10       Y=1
	               3: y <= ~y;		      //  JK  =  11       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_5_1_2(
    input cp, x,                               		 
    input y2, y1,				
    output ny2, ny1    		 	        
);
    wire k2j2;
    wire ny2n, ny1n;
    xor_gate U1(.a(x),.b(y1),.f(k2j2));				//结构化描述方式
    jk_flip_flop U2(.j(k2j2),.k(k2j2),.cp(cp),.q(ny2),.qn(ny2n));		//结构化描述方式
    jk_flip_flop U3(.j(1),.k(1),.cp(cp),.q(ny1),.qn(ny1n));		//结构化描述方式
endmodule

module example_5_1_2_exe(
    input sw_pin[7:0],                               		 //8个拨动开关
    input btn_1,				 //1个按钮
    output [15:0] led_pin    		 	//16个led灯            
);
    reg y2, y1;
    example_5_1_2 U(.cp(btn_1), .x(sw_pin[0]), .y2(y2), .y1(y1), .ny2(led_pin[0]), .ny1(led_pin[1]));
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