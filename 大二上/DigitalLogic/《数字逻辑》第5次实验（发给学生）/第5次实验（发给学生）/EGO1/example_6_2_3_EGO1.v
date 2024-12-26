//��Ϊ������ʽʵ������6.2��ģ4��1�����������루x1��x2��x3��Ϊ�������ϵ�S3��S2��S0������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module example_6_2_3(
    input x1, x2, x3,                               		 
    input y2, y1,	
    input rd,			
    output reg ny2, ny1, z    		 	        
);

    always @(*)                      //��Ϊ������ʽ
    begin
    if(rd==0)
        begin ny2 <= 1; ny1 <= 0; z <= 0; end
    else
        begin
	if(x1==1 & x2==0 & x3==0) begin
                        case({y2, y1})
	                0: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 10       z=0
	                1: begin ny2 <= 1; ny1 <= 0; z <= 1; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 10       z=1	               
		2: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 10       z=0	               
		3: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 10       z=0	               
                        endcase
                end

	if(x1==0 & x2==1 & x3==0) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 0; ny1 <= 0; z <= 1; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 00       z=1	               
		2: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 11       z=0	               
		3: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 00       z=0	               
                        endcase
                end

	if(x1==0 & x2==0 & x3==1) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 0; ny1 <= 0; z <= 1; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 00       z=1	               
		2: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 00       z=0	               
		3: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 01       z=0	               
                        endcase
                end
        end
    end

endmodule