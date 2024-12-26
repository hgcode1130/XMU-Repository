//������Ϊ������ʽʵ��4λ�����Ʋ��мӷ�������ǰ��λ��������AΪ�������ϵ���ߵ�4���������أ�����BΪ�������ϵ��ұߵ�4���������أ����C4Ϊ������������ߵ�1��LED�ƣ����FΪ�����������ұߵ�4��LED�ơ�

`timescale 1ns / 1ps	

module carry_lookahead_adder(
    input a3, a2, a1, a0, b3, b2, b1, b0, cin,                         		 
    output f3, f2, f1 ,f0, cout    	
);

    reg y3, y2, y1, y0, c4, c3, c2, c1;

    always @(*)                        //��Ϊ������ʽ
    begin
        {c1,y0} <= a0+b0+cin; 
        {c2,y1} <= a1+b1+c1; 
        {c3,y2} <= a2+b2+c2; 
        {c4,y3} <= a3+b3+c3; 
    end

    assign f0 = y0;
    assign f1 = y1;
    assign f2 = y2;
    assign f3 = y3;

    assign cout = c4;

endmodule

module carry_lookahead_adder_exe(
    input sw_pin[7:0],                               		 	//8����������
    output [15:0] led_pin    		 		//16��led��            
);

    carry_lookahead_adder U(.a3(sw_pin[0]), .a2(sw_pin[1]), .a1(sw_pin[2]), .a0(sw_pin[3]), .b3(sw_pin[4]), .b2(sw_pin[5]), .b1(sw_pin[6]), .b0(sw_pin[7]), .cin(0), .f3(led_pin[4]), .f2(led_pin[5]), .f1(led_pin[6]), .f0(led_pin[7]), .cout(led_pin[0]));

endmodule