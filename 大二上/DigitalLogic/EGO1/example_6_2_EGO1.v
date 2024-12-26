//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������6.2��ģ4��1�����������루x1��x2��x3��Ϊ�������ϵ�S3��S2��S0������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module not_gate(
    input a,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= ~a; 
    end
    assign f = y;
endmodule

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

module nand_gate3(
    input a,
    input b,
    input c,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= ~(a & b & c); 
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

module rs_flip_flop(
    input r, s,          
    output q, qn		
);
    reg y;

    always @(*)                     //��Ϊ������ʽ
    begin
                case({r,s})
	               0: y <= 1'bx;		      //  RS  =  00       Y=����
	               1: y <= 0;			      //  RS  =  01       Y=0
	               2: y <= 1;			      //  RS  =  10       Y=1
                endcase
    end

    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_2(
    input x1, x2, x3,                               		 
    input y2, y2n, y1, y1n,				
    output ny2, ny1, z    	
);

    wire s2, r2, s1, r1, t1, t2, t3, t4; 
    wire ny2n, ny1n;

    not_gate U1(.a(x1),.f(s2));					//�ṹ��������ʽ
    and_gate2 U2(.a(x3),.b(x3),.f(t1));				//�ṹ��������ʽ
    and_gate2 U3(.a(x2),.b(y1),.f(t2));				//�ṹ��������ʽ
    nor_gate2 U4(.a(t1),.b(t2),.f(r2));				//�ṹ��������ʽ
    nand_gate3 U5(.a(x2),.b(y2),.c(y1n),.f(s1));			//�ṹ��������ʽ
    and_gate2 U6(.a(x1),.b(x1),.f(t3));				//�ṹ��������ʽ
    and_gate2 U7(.a(x3),.b(y2n),.f(t4));				//�ṹ��������ʽ
    and_gate2 U8(.a(y1),.b(y1),.f(t5));				//�ṹ��������ʽ
    nor_gate3 U9(.a(t3),.b(t4),.c(t5),.f(r1));			//�ṹ��������ʽ
    rs_flip_flop U10(.r(r2),.s(s2),.q(ny2),.qn(ny2n));			//�ṹ��������ʽ
    rs_flip_flop U11(.r(r1),.s(s1),.q(ny1),.qn(ny1n));			//�ṹ��������ʽ
    nor_gate2 U12(.a(y2),.b(y1n),.f(z));				//�ṹ��������ʽ

endmodule

module example_6_2_exe(
    input btn_3, btn_2, btn_0,				 //3����ť
    output [15:0] led_pin    		 		//16��led��            
);

    reg y2, y2n, y1, y1n;

    example_6_2 U(.x1(btn_3), .x2(btn_2), .x3(btn_0), .y2(y2), .y2n(y2n), .y1(y1), .y1n(y1n), .ny2(led_pin[0]), .ny1(led_pin[1]), .z(led_pin[7]));

    initial begin
        y2=0;
        y2n=1;
        y1=0;
        y1n=1;
    end

    always @(*)                     		//��Ϊ������ʽ
    begin
	y2 <= led_pin[0];
	y2n <= ~led_pin[0];
	y1 <= led_pin[1];
	y1n <= ~led_pin[1];
    end

endmodule