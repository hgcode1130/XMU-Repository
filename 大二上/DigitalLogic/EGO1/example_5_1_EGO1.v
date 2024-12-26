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

module example_5_1(
    input sw_pin[7:0],                               		 //8����������
    input btn_1,				 //1����ť
    output [15:0] led_pin    		 	//16��led��            
);
    wire y1, y1n, y2, y2n, k2j2;
    jk_flip_flop U1(.j(1),.k(1),.cp(btn_1),.q(y1),.qn(y1n));		//�ṹ��������ʽ
    xor_gate U2(.a(sw_pin[0]),.b(y1),.f(k2j2));			//�ṹ��������ʽ
    jk_flip_flop U3(.j(k2j2),.k(k2j2),.cp(btn_1),.q(y2),.qn(y2n));		//�ṹ��������ʽ
   assign led_pin[0] = y2;
   assign led_pin[1] = y1;
endmodule