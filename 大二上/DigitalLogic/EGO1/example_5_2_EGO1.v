//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������5.2�ġ�101�����м����������x��CPΪ������������ߵĲ��������Լ�S1������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�LED�ơ�

`timescale 1ns / 1ps	

module nor_gate(
    input a,
    input b,
    input c,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= ~(a | b | c); 
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
    always @(posedge cp  or negedge rd)                     //��Ϊ������ʽ
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

module example_5_2(
    input cp,	
    input x,      
    input rd,                         		 
    input y2, y2n, y1, y1n,			 
    output ny2, ny2n, ny1, ny1n, z    		 	          
);
    wire xn, d2;
    nor_gate U1(.a(x),.b(y1n),.c(y2),.f(d2));			//�ṹ��������ʽ
    d_flip_flop U2(.d(d2),.cp(cp),.rd(rd),.q(ny2),.qn(ny2n));		//�ṹ��������ʽ
    d_flip_flop U3(.d(x),.cp(cp),.rd(rd),.q(ny1),.qn(ny1n));		//�ṹ��������ʽ
    nor_gate U4(.a(x),.b(x),.c(x),.f(xn));				//�ṹ��������ʽ
    nor_gate U5(.a(xn),.b(ny2n),.c(ny1),.f(z));			//�ṹ��������ʽ
endmodule