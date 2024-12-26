//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������6.3�ġ�x1 - x2 - x2�����м���������루x1��x2��Ϊ�������ϵ�S3��S2������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module and_gate2(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= a & b; 
    end
    assign f = y;
endmodule

module nor_gate2(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= ~(a | b); 
    end
    assign f = y;
endmodule

module nor_gate3(
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
    input cp,                               	  
    input d,      
    input rd,                                                   
    output q, qn		
);
    reg y;
    always @(posedge cp  or negedge rd)                     //��Ϊ������ʽ
    begin
        if(rd==0)
                y <= 0;
        else
                case(d)
	               0: y <= 0;			      //  D  =  0       Y=0
	               1: y <= 1;			      //  D  =  1       Y=1
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_3_2(
    input x1, x2,                               		 
    input y2, y1,	
    input rd,			
    output ny2, ny1, z    	
);

    wire cp2, cp1;
    wire t1, t2, t3, t4; 
    wire ny2n, ny1n;

    and_gate2 U1(.a(x1),.b(~y2),.f(t1));				//�ṹ��������ʽ
    and_gate2 U2(.a(x2),.b(y1),.f(t2));				//�ṹ��������ʽ
    and_gate2 U3(.a(x2),.b(y2),.f(t3));				//�ṹ��������ʽ
    nor_gate3 U4(.a(t1),.b(t2),.c(t3),.f(cp2));			//�ṹ��������ʽ

    and_gate2 U5(.a(x1),.b(y1),.f(t4));				//�ṹ��������ʽ
    nor_gate2 U6(.a(t3),.b(t4),.f(cp1));				//�ṹ��������ʽ

    d_flip_flop U7(.cp(cp2),.d(~y2),.rd(rd),.q(ny2),.qn(ny2n));		//�ṹ��������ʽ
    d_flip_flop U8(.cp(cp1),.d(~y1),.rd(rd),.q(ny1),.qn(ny1n));		//�ṹ��������ʽ

    and_gate2 U9(.a(y1),.b(y2),.f(z));				//�ṹ��������ʽ

endmodule