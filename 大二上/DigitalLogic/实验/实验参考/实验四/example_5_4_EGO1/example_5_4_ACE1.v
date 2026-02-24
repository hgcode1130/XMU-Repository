//结构化描述方式（子模块采用行为描述方式）实现例题5.4的3位串行输入移位寄存器，
//该电路的输入为x，状态为（y3、y2、y1），输出为Z，CP为时钟信号。

`timescale 1ns / 1ps	

module xor_gate(input a,input b,output f);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= a ^ b; 
    end
    assign f = y;
endmodule

module t_flip_flop(input t,input cp,output q, qn);
    reg y;
    always @(negedge cp)                     //行为描述方式
    begin
                case({t})
	               1: y <= ~y;			      //  t  =  1       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_5_4(
    input sw_pin[7:0],                               		 //8个拨动开关
    input btn_1,				 //1个按钮
    output [7:0] led_pin    		 	//8个led灯            
);
    wire y1, y1n, y2, y2n, y3, y3n, t1,t2,t3,f1,z;
	xor_gate U1(.a(sw_pin[7]),.b(y1),.f(t1));			//结构化描述方式
    t_flip_flop U2(.t(t1),.cp(btn_1),.q(y1),.qn(y1n));		//结构化描述方式
    xor_gate U3(.a(y1),.b(y2),.f(t2));			//结构化描述方式
    t_flip_flop U4(.t(t2),.cp(btn_1),.q(y2),.qn(y2n));		//结构化描述方式
	xor_gate U5(.a(y2),.b(y3),.f(t3));			//结构化描述方式
    t_flip_flop U6(.t(t3),.cp(btn_1),.q(y3),.qn(y3n));		//结构化描述方式
	xor_gate U7(.a(y2),.b(y3),.f(f1));			//结构化描述方式
	xor_gate U8(.a(y1),.b(f1),.f(z));			//结构化描述方式
   assign led_pin[7] = y3;
   assign led_pin[6] = y2;
   assign led_pin[5] = y1;
   assign led_pin[0] = z;
endmodule