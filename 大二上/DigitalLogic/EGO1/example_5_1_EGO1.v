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

module example_5_1(
    input sw_pin[7:0],                               		 //8个拨动开关
    input btn_1,				 //1个按钮
    output [15:0] led_pin    		 	//16个led灯            
);
    wire y1, y1n, y2, y2n, k2j2;
    jk_flip_flop U1(.j(1),.k(1),.cp(btn_1),.q(y1),.qn(y1n));		//结构化描述方式
    xor_gate U2(.a(sw_pin[0]),.b(y1),.f(k2j2));			//结构化描述方式
    jk_flip_flop U3(.j(k2j2),.k(k2j2),.cp(btn_1),.q(y2),.qn(y2n));		//结构化描述方式
   assign led_pin[0] = y2;
   assign led_pin[1] = y1;
endmodule