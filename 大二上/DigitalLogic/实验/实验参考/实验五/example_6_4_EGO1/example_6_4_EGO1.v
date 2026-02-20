//结构化描述方式（子模块采用行为描述方式）实现例题6.4的模8加1计数器
//输入（x）为开发板上的KEY1按键，状态（y3、y2、y1）和输出Z为开发板上最左边的3个LED灯以及最右边的1个LED灯。

`timescale 1ns / 1ps	

module and_gate(
    input a,
    input b,
    input c,
	input d,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= a & b & c & d; 
    end
    assign f = y;
endmodule

module t_flip_flop(
    input t,                               	  
    input cp,                                                         
    output q, qn		
);
    reg y;
    always @(negedge cp)                     //行为描述方式
    begin
                case({t})
	               1: y <= ~y;			      //  t = 1       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_4(
    input x,                               		 
    input y3,y2, y1,				
    output ny3,ny2, ny1, z    		 	        
);
    wire ny3n,ny2n, ny1n;

    t_flip_flop U1(.t(1),.cp(x),.q(ny1),.qn(ny1n));		//结构化描述方式
    t_flip_flop U2(.t(1),.cp(y1),.q(ny2),.qn(ny2n));		//结构化描述方式
	t_flip_flop U3(.t(1),.cp(y2),.q(ny3),.qn(ny3n));		//结构化描述方式
    and_gate U4(.a(x),.b(y1),.c(y2),.d(y3),.f(z));				//结构化描述方式

endmodule

module example_6_1_exe(
    input btn_1,				 //KEY1按钮
    output [7:0] led_pin    		 	//8个led灯            
);
    reg y3, y2, y1;
    example_6_4 U(.x(btn_1),.y3(y3), .y2(y2), .y1(y1),.ny3(led_pin[7]), .ny2(led_pin[6]), .ny1(led_pin[5]), .z(led_pin[0]));
    initial begin
		y3=0;
        y2=0;
        y1=0;
    end
    always @(*)                     		//行为描述方式
    begin
	y3 <= led_pin[7];
	y2 <= led_pin[6];
	y1 <= led_pin[5];
    end
endmodule
