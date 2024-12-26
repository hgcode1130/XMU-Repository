//������Ϊ������ʽʵ������6.3�ġ�x1 - x2 - x2�����м���������루x1��x2��Ϊ�������ϵ�S3��S2������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module example_6_3_3(
    input x1, x2,                               		 
    input y2, y1,
    input rd,				
    output reg ny2, ny1, z    		 	        
);

    always @(*)                      //��Ϊ������ʽ
    begin
         if(rd==0)
                begin ny2 <= 0; ny1 <= 0; z <= 0; end
         else
	if(x1 == 1 & x2 == 0)
                        case({y2, y1})
	                0: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 10       z=0
	                1: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 10       z=0	               
		2: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 10       z=0	               
		3: begin ny2 <= 1; ny1 <= 0; z <= 1; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 10       z=1	               
                        endcase
	if(x1 == 0 & x2 == 1)
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 11       z=0	               
		2: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 01       z=0	               
		3: begin ny2 <= 0; ny1 <= 0; z <= 1; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 00       z=1	               
                        endcase
    end

endmodule