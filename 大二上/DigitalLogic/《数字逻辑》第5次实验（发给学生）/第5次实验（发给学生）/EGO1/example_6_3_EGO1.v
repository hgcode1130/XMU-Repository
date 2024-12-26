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
    output q, qn		
);
    reg y;
    always @(posedge cp)                     //��Ϊ������ʽ
    begin
                case(d)
	               0: y <= 0;			      //  D  =  0       Y=0
	               1: y <= 1;			      //  D  =  1       Y=1
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_3(
    input x1, x2,                               		 
    input y2, y1,				
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

    d_flip_flop U7(.cp(cp2),.d(~y2),.q(ny2),.qn(ny2n));		//�ṹ��������ʽ
    d_flip_flop U8(.cp(cp1),.d(~y1),.q(ny1),.qn(ny1n));		//�ṹ��������ʽ

    and_gate2 U9(.a(y1),.b(y2),.f(z));				//�ṹ��������ʽ

endmodule

module example_6_3_exe(
    input btn_3, btn_2,				 //S3��S2��ť
    output [15:0] led_pin    		 		//16��led��            
);

    reg y2, y1;

    example_6_3 U(.x1(btn_3), .x2(btn_2), .y2(y2), .y1(y1), .ny2(led_pin[0]), .ny1(led_pin[1]), .z(led_pin[7]));

    initial begin
        y2=0;
        y1=0;
    end

    always @(*)                     		//��Ϊ������ʽ
    begin
	y2 <= led_pin[0];
	y1 <= led_pin[1];
    end

endmodule