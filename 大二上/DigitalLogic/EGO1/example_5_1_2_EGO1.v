//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������5.1��2λ��������������������������ϵ����루x��CP��Ϊ������������ߵĲ��������Լ�S1�����������y2��y1��Ϊ������������ߵ�2��LED�ơ�

`timescale 1ns / 1ps	

module xor_gate(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= a ^ b; 
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

module example_5_1_2(
    input cp, x,                               		 
    input y2, y1,				
    output ny2, ny1    		 	        
);
    wire k2j2;
    wire ny2n, ny1n;
    xor_gate U1(.a(x),.b(y1),.f(k2j2));				//�ṹ��������ʽ
    jk_flip_flop U2(.j(k2j2),.k(k2j2),.cp(cp),.q(ny2),.qn(ny2n));		//�ṹ��������ʽ
    jk_flip_flop U3(.j(1),.k(1),.cp(cp),.q(ny1),.qn(ny1n));		//�ṹ��������ʽ
endmodule

module example_5_1_2_exe(
    input sw_pin[7:0],                               		 //8����������
    input btn_1,				 //1����ť
    output [15:0] led_pin    		 	//16��led��            
);
    reg y2, y1;
    example_5_1_2 U(.cp(btn_1), .x(sw_pin[0]), .y2(y2), .y1(y1), .ny2(led_pin[0]), .ny1(led_pin[1]));
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