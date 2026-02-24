//行为描述方式实现例题5.3的串行加法器，
//该电路的输入为x1、x2，状态为y，输出为Z，CP为时钟信号。

`timescale 1ns / 1ps	

module example_5_3_1(
    input cp,
    input x1,x2,                               		 	
    input y1,			 
    output reg ny1, z    		 	          
);

    always @(negedge cp)                      //行为描述方式

    begin
                case({y1, x1, x2})
	    0: begin ny1 <= 0; z=0;  end			      //  y1 x1 x2 = 000       y1n+1 = 0       z=0
	    1: begin ny1 <= 0; z=1;  end			      //  y1 x1 x2 = 001       y1n+1 = 0       z=1
		2: begin ny1 <= 0; z=1;  end			      //  y1 x1 x2 = 010       y1n+1 = 0       z=1
		3: begin ny1 <= 1; z=0;  end			      //  y1 x1 x2 = 011       y1n+1 = 1       z=0
		4: begin ny1 <= 0; z=1;  end			      //  y1 x1 x2 = 100       y1n+1 = 0       z=1
		5: begin ny1 <= 1; z=0;  end			      //  y1 x1 x2 = 101       y1n+1 = 1       z=0
		6: begin ny1 <= 1; z=0;  end			      //  y1 x1 x2 = 110       y1n+1 = 1       z=0
		7: begin ny1 <= 1; z=1;  end			      //  y1 x1 x2 = 111       y1n+1 = 1       z=1
                endcase
    end

endmodule