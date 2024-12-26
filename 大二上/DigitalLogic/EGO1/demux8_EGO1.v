//������Ϊ������ʽʵ��8·��·��������DEMUX�������루D��Ϊ�������ϵ�����ߵ�1���������أ����루A2��A1��A0��Ϊ�������ϵ����ұߵ�3���������أ������f0��f1��f2��f3��f4��f5��f6��f7��Ϊ�������ϵ�8��LED�ơ�

`timescale 1ns / 1ps	

module demux8(
    input d, a2, a1, a0,                         		 
    output f0, f1, f2, f3, f4, f5, f6, f7    	
);
    reg y0, y1, y2, y3, y4, y5, y6, y7;

    always @(*)                        //��Ϊ������ʽ
    begin
    case(d)
          0:
          begin
          if(a2==0 & a1==0 & a0==0)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==0 & a1==0 & a0==1)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==0 & a1==1 & a0==0)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==0 & a1==1 & a0==1)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==1 & a1==0 & a0==0)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==1 & a1==0 & a0==1)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==1 & a1==1 & a0==0)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==1 & a1==1 & a0==1)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end
          end

          1:
          begin
          if(a2==0 & a1==0 & a0==0)
                begin y0 <= 1; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==0 & a1==0 & a0==1)
                begin y0 <= 0; y1 <= 1; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==0 & a1==1 & a0==0)
                begin y0 <= 0; y1 <= 0; y2 <= 1; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==0 & a1==1 & a0==1)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 1; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==1 & a1==0 & a0==0)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 1; y5 <= 0; y6 <= 0; y7 <= 0; end

          if(a2==1 & a1==0 & a0==1)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 1; y6 <= 0; y7 <= 0; end

          if(a2==1 & a1==1 & a0==0)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 1; y7 <= 0; end

          if(a2==1 & a1==1 & a0==1)
                begin y0 <= 0; y1 <= 0; y2 <= 0; y3 <= 0; y4 <= 0; y5 <= 0; y6 <= 0; y7 <= 1; end
          end
    endcase
    end

    assign f0 = y0;
    assign f1 = y1;
    assign f2 = y2;
    assign f3 = y3;
    assign f4 = y4;
    assign f5 = y5;
    assign f6 = y6;
    assign f7 = y7;

endmodule

module demux8_exe(
    input sw_pin[7:0],                               		 	//8����������
    output [15:0] led_pin    		 		//16��led��            
);

    demux8 U(.d(sw_pin[0]), .a2(sw_pin[5]), .a1(sw_pin[6]), .a0(sw_pin[7]), .f0(led_pin[0]), .f1(led_pin[1]), .f2(led_pin[2]), .f3(led_pin[3]), .f4(led_pin[4]), .f5(led_pin[5]), .f6(led_pin[6]), .f7(led_pin[7]));

endmodule