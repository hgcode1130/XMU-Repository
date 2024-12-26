//采用行为描述方式实现74138（3-8译码器）芯片，输入（S1、/S2、/S3）为开发板上的最左边的3个拨动开关，输入（A2、A1、A0）为开发板上的最右边的3个拨动开关，输出（/Y0、/Y1、/Y2、/Y3、/Y4、/Y5、/Y6、/Y7）为开发板上的8个LED灯。

`timescale 1ns / 1ps	

module ttl74138(
    input s1, s2, s3, a2, a1, a0,                         		 
    output y0, y1, y2, y3, y4, y5, y6, y7    	
);
    wire s23;
    reg f0, f1, f2, f3, f4, f5, f6, f7;

    assign s23 = s2 | s3;

    always @(*)                        //行为描述方式
    begin
          if(s1==1 & s23==0 & a2==0 & a1==0 & a0==0)
                begin f0 <= 0; f1 <= 1; f2 <= 1; f3 <= 1; f4 <= 1; f5 <= 1; f6 <= 1; f7 <= 1; end

          if(s1==1 & s23==0 & a2==0 & a1==0 & a0==1)
                begin f0 <= 1; f1 <= 0; f2 <= 1; f3 <= 1; f4 <= 1; f5 <= 1; f6 <= 1; f7 <= 1; end

          if(s1==1 & s23==0 & a2==0 & a1==1 & a0==0)
                begin f0 <= 1; f1 <= 1; f2 <= 0; f3 <= 1; f4 <= 1; f5 <= 1; f6 <= 1; f7 <= 1; end

          if(s1==1 & s23==0 & a2==0 & a1==1 & a0==1)
                begin f0 <= 1; f1 <= 1; f2 <= 1; f3 <= 0; f4 <= 1; f5 <= 1; f6 <= 1; f7 <= 1; end

          if(s1==1 & s23==0 & a2==1 & a1==0 & a0==0)
                begin f0 <= 1; f1 <= 1; f2 <= 1; f3 <= 1; f4 <= 0; f5 <= 1; f6 <= 1; f7 <= 1; end

          if(s1==1 & s23==0 & a2==1 & a1==0 & a0==1)
                begin f0 <= 1; f1 <= 1; f2 <= 1; f3 <= 1; f4 <= 1; f5 <= 0; f6 <= 1; f7 <= 1; end

          if(s1==1 & s23==0 & a2==1 & a1==1 & a0==0)
                begin f0 <= 1; f1 <= 1; f2 <= 1; f3 <= 1; f4 <= 1; f5 <= 1; f6 <= 0; f7 <= 1; end

          if(s1==1 & s23==0 & a2==1 & a1==1 & a0==1)
                begin f0 <= 1; f1 <= 1; f2 <= 1; f3 <= 1; f4 <= 1; f5 <= 1; f6 <= 1; f7 <= 0; end

          if(s1==0)
                begin f0 <= 1; f1 <= 1; f2 <= 1; f3 <= 1; f4 <= 1; f5 <= 1; f6 <= 1; f7 <= 1; end

          if(s23==1)
                begin f0 <= 1; f1 <= 1; f2 <= 1; f3 <= 1; f4 <= 1; f5 <= 1; f6 <= 1; f7 <= 1; end 
    end

    assign y0 = f0;
    assign y1 = f1;
    assign y2 = f2;
    assign y3 = f3;
    assign y4 = f4;
    assign y5 = f5;
    assign y6 = f6;
    assign y7 = f7;

endmodule

module ttl74138_exe(
    input sw_pin[7:0],                               		 	//8个拨动开关
    output [15:0] led_pin    		 		//16个led灯            
);

    ttl74138 U(.s1(sw_pin[0]), .s2(sw_pin[1]), .s3(sw_pin[2]), .a2(sw_pin[5]), .a1(sw_pin[6]), .a0(sw_pin[7]), .y0(led_pin[0]), .y1(led_pin[1]), .y2(led_pin[2]), .y3(led_pin[3]), .y4(led_pin[4]), .y5(led_pin[5]), .y6(led_pin[6]), .y7(led_pin[7]));

endmodule