//��Ϊ������ʽʵ������Ź��ɵĻ���R-S��������2������Ϊ����ߵ�2���������أ����Ϊ����ߵ�LED��

`timescale 1ns / 1ps	

module rs_flip_flop(
    input [7:0] sw_pin,                               	//8����������
    output reg [15:0] led_pin    		//16��led��
);

always @(*)
    begin

      if(sw_pin[0]==0 & sw_pin[1]==1)		//R S =0 1             /Q=1    Q=0     
         begin 
              led_pin[0] <= 1; 			//    ��� /Q
              led_pin[1] <= 0; 			//    ���  Q
         end

      if(sw_pin[0]==1 & sw_pin[1]==0)		//R S =1 0             /Q=0    Q=1     
         begin 
              led_pin[0] <= 0; 			//    ��� /Q
              led_pin[1] <= 1; 			//    ���  Q
         end

      if(sw_pin[0]==0 & sw_pin[1]==0)		//R S =0 0             /Q=����    Q=����     
         begin 
              led_pin[0] <= 1'bx; 			//    ��� /Q
              led_pin[1] <= 1'bx; 			//    ���  Q
         end

    end

endmodule