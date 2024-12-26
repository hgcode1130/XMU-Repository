//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ��4λ�����ƴ��мӷ���������AΪ�������ϵ���ߵ�4���������أ�����BΪ�������ϵ��ұߵ�4���������أ����C4Ϊ������������ߵ�1��LED�ƣ����FΪ�����������ұߵ�4��LED�ơ�

`timescale 1ns / 1ps	

module full_adder(
    input a,
    input b,
    input cin,
    output f,
    output cout                               
);
    reg y1, y2;

    always @(*)                        //��Ϊ������ʽ
    begin
        {y2,y1} <= a+b+cin; 
    end

    assign f = y1;
    assign cout = y2;

endmodule

module serial_adder(
    input a3, a2, a1, a0, b3, b2, b1, b0, cin,                         		 
    output f3, f2, f1 ,f0, cout    	
);
    wire c1, c2, c3;

    full_adder U1(.a(a0),.b(b0),.cin(cin),.f(f0),.cout(c1));				//�ṹ��������ʽ
    full_adder U2(.a(a1),.b(b1),.cin(c1),.f(f1),.cout(c2));				//�ṹ��������ʽ
    full_adder U3(.a(a2),.b(b2),.cin(c2),.f(f2),.cout(c3));				//�ṹ��������ʽ
    full_adder U4(.a(a3),.b(b3),.cin(c3),.f(f3),.cout(cout));				//�ṹ��������ʽ

endmodule

module serial_adder_exe(
    input sw_pin[7:0],                               		 	//8����������
    output [15:0] led_pin    		 		//16��led��            
);

    serial_adder U(.a3(sw_pin[0]), .a2(sw_pin[1]), .a1(sw_pin[2]), .a0(sw_pin[3]), .b3(sw_pin[4]), .b2(sw_pin[5]), .b1(sw_pin[6]), .b0(sw_pin[7]), .cin(0), .f3(led_pin[4]), .f2(led_pin[5]), .f1(led_pin[6]), .f0(led_pin[7]), .cout(led_pin[0]));

endmodule