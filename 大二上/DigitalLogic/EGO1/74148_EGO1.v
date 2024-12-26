//采用行为描述方式实现74148（8-3线优先编码器）芯片，输入（/I0、/I1、/I2、/I3、/I4、/I5、/I6、/I7）为开发板上的8个拨动开关，输出（/QC、/QB、/QA、/QEX、OS）为开发板上最左边的5个LED灯。

`timescale 1ns / 1ps	

module ttl74148(
    input i0, i1, i2, i3, i4, i5, i6, i7,                         		 
    output qc, qb, qa, qex, os    	
);
    reg fqc, fqb, fqa, fqex, fos;

    always @(*)                        //行为描述方式
    begin
          if(i0==1 & i1==1 & i2==1 & i3==1 & i4==1 & i5==1 & i6==1 & i7==1)
                begin fqc <= 1; fqb <= 1; fqa <= 1; fqex <= 1; fos <= 0; end

          if(i7==0)
                begin fqc <= 0; fqb <= 0; fqa <= 0; fqex <= 0; fos <= 1; end

          if(i6==0 & i7==1)
                begin fqc <= 0; fqb <= 0; fqa <= 1; fqex <= 0; fos <= 1; end

          if(i5==0 & i6==1 & i7==1)
                begin fqc <= 0; fqb <= 1; fqa <= 0; fqex <= 0; fos <= 1; end

          if(i4==0 & i5==1 & i6==1 & i7==1)
                begin fqc <= 0; fqb <= 1; fqa <= 1; fqex <= 0; fos <= 1; end

          if(i3==0 & i4==1 & i5==1 & i6==1 & i7==1)
                begin fqc <= 1; fqb <= 0; fqa <= 0; fqex <= 0; fos <= 1; end

          if(i2==0 & i3==1 & i4==1 & i5==1 & i6==1 & i7==1)
                begin fqc <= 1; fqb <= 0; fqa <= 1; fqex <= 0; fos <= 1; end

          if(i1==0 & i2==1 & i3==1 & i4==1 & i5==1 & i6==1 & i7==1)
                begin fqc <= 1; fqb <= 1; fqa <= 0; fqex <= 0; fos <= 1; end

          if(i0==0 & i1==1 & i2==1 & i3==1 & i4==1 & i5==1 & i6==1 & i7==1)
                begin fqc <= 1; fqb <= 1; fqa <= 1; fqex <= 0; fos <= 1; end
    end

    assign qc = fqc;
    assign qb = fqb;
    assign qa = fqa;
    assign qex = fqex;
    assign os = fos;

endmodule

module ttl74148_exe(
    input sw_pin[7:0],                               		 	//8个拨动开关
    output [15:0] led_pin    		 		//16个led灯            
);

    ttl74148 U(.i0(sw_pin[0]), .i1(sw_pin[1]), .i2(sw_pin[2]), .i3(sw_pin[3]), .i4(sw_pin[4]), .i5(sw_pin[5]), .i6(sw_pin[6]), .i7(sw_pin[7]), .qc(led_pin[0]), .qb(led_pin[1]), .qa(led_pin[2]), .qex(led_pin[3]), .os(led_pin[4]));

endmodule