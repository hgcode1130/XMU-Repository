//��Ϊ������ʽʵ������5.1��2λ��������������������������ϵ����루x��CP��Ϊ������������ߵĲ��������Լ�S1�����������y2��y1��Ϊ������������ߵ�2��LED�ơ�

`timescale 1ns / 1ps	

module example_5_1_1(
    input sw_pin[7:0],                               		 	//8����������
    input btn_1,				 	//1����ť
    output reg [15:0] led_pin    		 	//16��led��            
);

    always @(negedge btn_1)                      //��Ϊ������ʽ

    begin
                case({sw_pin[0], led_pin[0], led_pin[1]})
	                0: begin led_pin[0] <= 0; led_pin[1] <= 1; end			      //  x y2 y1 = 000       y2n+1 y1n+1 = 01
	                1: begin led_pin[0] <= 1; led_pin[1] <= 0; end			      //  x y2 y1 = 001       y2n+1 y1n+1 = 10	               
		2: begin led_pin[0] <= 1; led_pin[1] <= 1; end			      //  x y2 y1 = 010       y2n+1 y1n+1 = 11	               
		3: begin led_pin[0] <= 0; led_pin[1] <= 0; end			      //  x y2 y1 = 011       y2n+1 y1n+1 = 00	               
		4: begin led_pin[0] <= 1; led_pin[1] <= 1; end			      //  x y2 y1 = 100       y2n+1 y1n+1 = 11	               
		5: begin led_pin[0] <= 0; led_pin[1] <= 0; end			      //  x y2 y1 = 101       y2n+1 y1n+1 = 00	               
		6: begin led_pin[0] <= 0; led_pin[1] <= 1; end			      //  x y2 y1 = 110       y2n+1 y1n+1 = 01
		7: begin led_pin[0] <= 1; led_pin[1] <= 0; end			      //  x y2 y1 = 111       y2n+1 y1n+1 = 10
                endcase
    end

endmodule