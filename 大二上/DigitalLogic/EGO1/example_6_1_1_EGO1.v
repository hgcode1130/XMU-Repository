//������Ϊ������ʽʵ������6.1��ģ4��1�����������루x��Ϊ�������ϵ�S1������״̬��y2��y1�������ZΪ������������ߵ�2��LED���Լ����ұߵ�1��LED�ơ�

`timescale 1ns / 1ps	

module example_6_1_1(
    input x,                               		 
    input y2, y1,				
    output reg ny2, ny1, z    		 	        
);

    always @(negedge x)                      	//��Ϊ������ʽ
    begin
                case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 01       z=0
	                1: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 10       z=0	               
		2: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 11       z=0	               
		3: begin ny2 <= 0; ny1 <= 0; z <= 1; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 00       z=1	               
                endcase
    end

endmodule

module example_6_1_1_exe(
    input btn_1,				 //S1��ť
    output [15:0] led_pin    		 	//16��led��            
);

    reg y2, y1;

    example_6_1_1 U(.x(btn_1), .y2(y2), .y1(y1), .ny2(led_pin[0]), .ny1(led_pin[1]), .z(led_pin[7]));

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