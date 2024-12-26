//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������6.1��ģ4��1�����������루x��Ϊ�������ϵ�S1������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module and_gate(
    input a,
    input b,
    input c,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= a & b & c; 
    end
    assign f = y;
endmodule

module jk_flip_flop(
    input j, k,                               	  
    input cp,    
    input rd,                                                     
    output q, qn		
);
    reg y;
    always @(negedge cp  or negedge rd)                     //��Ϊ������ʽ
    begin
       if(rd==0)  	                                           	        //  rd=0         y=0
                y <= 0;
       else                                                                           //  rd=1            
                case({j,k})
	               1: y <= 0;			      //  JK  =  01       Y=0
	               2: y <= 1;			      //  JK  =  10       Y=1
	               3: y <= ~y;		      //  JK  =  11       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_1_2(
    input x,                               		 
    input y2, y1,	
    input rd,			
    output ny2, ny1, z    		 	        
);
    wire ny2n, ny1n;
    jk_flip_flop U1(.j(1),.k(1),.cp(x),.rd(rd),.q(ny1),.qn(ny1n));		//�ṹ��������ʽ
    jk_flip_flop U2(.j(1),.k(1),.cp(y1),.rd(rd),.q(ny2),.qn(ny2n));		//�ṹ��������ʽ
    and_gate U3(.a(x),.b(y1),.c(y2),.f(z));				//�ṹ��������ʽ
endmodule