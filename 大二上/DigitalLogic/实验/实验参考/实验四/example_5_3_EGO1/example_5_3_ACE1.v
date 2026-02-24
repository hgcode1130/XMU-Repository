`timescale 1ns / 1ps	

module nand_gate(input a,input b,output f);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~(a & b); 
    end
    assign f = y;
endmodule

module xor_gate(input a,input b,output f);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= (a ^ b); 
    end
    assign f = y;
endmodule

module d_flip_flop(input d,input cp,output q, qn);
    reg y;
    always @(negedge cp)                     //行为描述方式
    begin
                case(d)
	               0: y <= 0;			      //  D  =  0       Y=0
	               1: y <= 1;			      //  D  =  1       Y=1
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_5_3(
    input cp,	
    input x1,x2,                           		 
    input y1, y1n,	 
    output ny1, ny1n, z    		 	          
);
    wire f1,f2,f3,d1;
    xor_gate U1(.a(x1),.b(x2),.f(f1));			//结构化描述方式
	nand_gate U2(.a(x1),.b(x2),.f(f2));			//结构化描述方式
    d_flip_flop U3(.d(d1),.cp(cp),.q(ny1),.qn(ny1n));			//结构化描述方式
    nand_gate U4(.a(ny1),.b(f1),.f(f3));				//结构化描述方式
	nand_gate U5(.a(f2),.b(f3),.f(d1));				//结构化描述方式
    xor_gate U6(.a(f1),.b(ny1),.f(z));			//结构化描述方式
endmodule