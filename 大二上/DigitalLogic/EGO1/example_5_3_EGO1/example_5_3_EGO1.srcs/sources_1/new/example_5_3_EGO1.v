
`timescale 1ns / 1ps	

module nor_gate(
    input a,
    input b,
    input c,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~(a | b | c); 
    end
    assign f = y;
endmodule

module nand_gate(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= ~(a | b ); 
    end
    assign f = y;
endmodule

module one_gate(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //行为描述方式
    begin
        y <= (a ^ b ); 
    end
    assign f = y;
endmodule

module d_flip_flop(
    input d,                               	  
    input cp,     
    input rd,                                                    
    output q, qn		
);
    reg y;
    always @(posedge cp  or negedge rd)                     //行为描述方式
    begin
       if(rd==0)  	                                           	        //  rd=0         y=0
                y <= 0;
       else                                                                           //  rd=1            
                case(d)
	               0: y <= 0;			      //  d  =  0       y=0
	               1: y <= 1;			      //  d  =  1       y=1
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_5_3(
    input cp,	
    input x1, x2,      
    input rd,                         		 
    input y, yn,			 
    output ny, nyn, z    		 	          
);
    wire f1, f2, f3, d;
    one_gate U1(.a(x1),.b(x2),.f(f1));
    nand_gate U2(.a(f1),.b(y),.f(f2));
    nand_gate U3(.a(x1),.b(x2),.f(f3));
    nand_gate U4(.a(f2),.b(f3),.f(d));
    d_flip_flop U5(.d(d),.cp(cp),.rd(rd),.q(ny),.qn(nyn));
    one_gate U6(.a(ny),.b(f1),.f(z));
    
endmodule
