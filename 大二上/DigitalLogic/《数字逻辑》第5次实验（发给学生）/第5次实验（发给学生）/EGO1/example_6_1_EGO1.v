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
    output q, qn		
);
    reg y;
    always @(negedge cp)                     //��Ϊ������ʽ
    begin
                case({j,k})
	               1: y <= 0;			      //  JK  =  01       Y=0
	               2: y <= 1;			      //  JK  =  10       Y=1
	               3: y <= ~y;		      //  JK  =  11       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_6_1(
    input x,                               		 
    input y2, y1,				
    output ny2, ny1, z    		 	        
);
    wire ny2n, ny1n;

    jk_flip_flop U1(.j(1),.k(1),.cp(x),.q(ny1),.qn(ny1n));		//�ṹ��������ʽ
    jk_flip_flop U2(.j(1),.k(1),.cp(y1),.q(ny2),.qn(ny2n));		//�ṹ��������ʽ
    and_gate U3(.a(x),.b(y1),.c(y2),.f(z));				//�ṹ��������ʽ

endmodule

module example_6_1_exe(
    input btn_1,				 //S1��ť
    output [15:0] led_pin    		 	//16��led��            
);
    reg y2, y1;
    example_6_1 U(.x(btn_1), .y2(y2), .y1(y1), .ny2(led_pin[0]), .ny1(led_pin[1]), .z(led_pin[7]));
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
