//������Ϊ������ʽʵ������4.1�Ĳ�һ�µ�·������Ϊ����ߵ�3���������أ����Ϊ����ߵ�LED�ơ�

`timescale 1ns / 1ps	

module example_4_1_1(
    input sw_pin[7:0],            	                   		 //8����������
    output reg [15:0] led_pin    		 	//16��led��            
);

always @(*)					//��Ϊ������ʽ
begin
                case({sw_pin[0],sw_pin[1],sw_pin[2]})
	               0: led_pin[0] <= 0;			    //  ABC=000   F=0
	               1: led_pin[0] <= 1;			    //  ABC=001   F=1
	               2: led_pin[0] <= 1;			    //  ABC=010   F=1
	               3: led_pin[0] <= 1;			    //  ABC=011   F=1
	               4: led_pin[0] <= 1;			    //  ABC=100   F=1
	               5: led_pin[0] <= 1;			    //  ABC=101   F=1
	               6: led_pin[0] <= 1;			    //  ABC=110   F=1
	               7: led_pin[0] <= 0;			    //  ABC=111   F=0
                endcase
end

endmodule