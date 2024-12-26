//��Ϊ������ʽʵ������5.2�ġ�101�����м����������x��CPΪ������������ߵĲ��������Լ�S1������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�LED�ơ�

`timescale 1ns / 1ps	

module example_5_2_1(
    input cp,
    input x,        
    input rd,                       		 	
    input y2, y1,			 
    output reg ny2, ny1, z    		 	          
);

    always @(posedge cp  or negedge rd)                      //��Ϊ������ʽ

    begin
       if(rd==0)  	                                           	        //  rd=0         
                begin ny2 <= 0; ny1 <= 0; z=0; end
       else                                                                           //  rd=1            
                case({y2, y1, x})
	                0: begin ny2 <= 0; ny1 <= 0; z=0; end			      //  y2 y1 x = 000       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 0; ny1 <= 1; z=0;  end			      //  y2 y1 x = 001       y2n+1 y1n+1 = 01       z=0	               
		2: begin ny2 <= 1; ny1 <= 0; z=0;  end			      //  y2 y1 x = 010       y2n+1 y1n+1 = 10       z=0	               
		3: begin ny2 <= 0; ny1 <= 1; z=0;  end			      //  y2 y1 x = 011       y2n+1 y1n+1 = 01       z=0           
		4: begin ny2 <= 0; ny1 <= 0; z=0;  end			      //  y2 y1 x = 100       y2n+1 y1n+1 = 00       z=0	               
		5: begin ny2 <= 0; ny1 <= 1; z=1;  end			      //  y2 y1 x = 101       y2n+1 y1n+1 = 01       z=1	               
		6: begin ny2 <= 0; ny1 <= 0; z=0;  end			      //  y2 y1 x = 110       y2n+1 y1n+1 = 00       z=0
		7: begin ny2 <= 0; ny1 <= 1; z=0;  end			      //  y2 y1 x = 111       y2n+1 y1n+1 = 01       z=0
                endcase
    end

endmodule