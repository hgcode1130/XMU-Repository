//��Ϊ������ʽʵ��2�������ţ�2������Ϊ����ߵ�2���������أ����Ϊ����ߵ�LED��

`timescale 1ns / 1ps

module andgate_1(
    input sw_pin[7:0],                              		 //8����������
    output reg [15:0] led_pin    		//16��led��
);

always @(*)		//��Ϊ������ʽ
begin
   led_pin[0] <= sw_pin[0] & sw_pin[1]; 
end

endmodule