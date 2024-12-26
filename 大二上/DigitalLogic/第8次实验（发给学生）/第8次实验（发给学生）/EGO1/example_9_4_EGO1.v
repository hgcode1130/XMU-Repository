//采用行为描述方式实现9.4小节的汽车尾灯控制器电路
//输入为开发板上最左边的2个拨动开关（K1、K0）
//输出为开发板上最左边的3个LED灯（L1、L2、L3）、最右边的3个LED灯（R1、R2、R3）

`timescale 1ns / 1ps

module example_9_4(
    input sys_clk_in,
    input sys_rst_n,
    input sw_pin[7:0],            	                   		//8个拨动开关
    output reg [15:0] led_pin    			//16个led灯
);

    reg [24 : 0] cnt_reg; 
    reg [2 : 0] six_reg;
		
    always @ (posedge sys_clk_in)		//延时计数
    begin
        if (!sys_rst_n) 
            cnt_reg <= 0; 
        else
            cnt_reg <= cnt_reg + 1;
    end

    always @ (posedge sys_clk_in) 	//six_reg计数：0-5           
    begin
        if (!sys_rst_n)
            six_reg <= 3'b000; 
        else if (cnt_reg == 25'h1ffffff) 	//调整 25'h1ffffff 这个值，可以改变LED灯的闪烁时间，值小则闪烁快，值大则闪烁慢
        begin
            if (six_reg == 3'b110) 
                six_reg <= 3'b000;
            else
                six_reg <= six_reg + 1;  	
        end
    end

    always @ (posedge sys_clk_in) 	//6个LED轮流亮
    begin
        if(sw_pin[0] == 0 && sw_pin[1] ==0)
            begin
	led_pin[0] <= 0;
	led_pin[1] <= 0;
	led_pin[2] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
            end 
        if (sw_pin[0] == 0 && sw_pin[1] ==1)
            begin
              if(six_reg == 0)
              begin
	led_pin[0] <= 0;
	led_pin[1] <= 0;
	led_pin[2] <= 0;
	led_pin[5] <= 1;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
              end
              if(six_reg == 2)
              begin
	led_pin[0] <= 0;
	led_pin[1] <= 0;
	led_pin[2] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 1;
	led_pin[7] <= 0;
              end
              if(six_reg == 4)
              begin
	led_pin[0] <= 0;
	led_pin[1] <= 0;
	led_pin[2] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 1;
              end
            end 
        if (sw_pin[0] == 1 && sw_pin[1] ==0)
            begin
              if(six_reg == 0)
              begin
	led_pin[0] <= 0;
	led_pin[1] <= 0;
	led_pin[2] <= 1;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
              end
              if(six_reg == 2)
              begin
	led_pin[0] <= 0;
	led_pin[1] <= 1;
	led_pin[2] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
              end
              if(six_reg == 4)
              begin
	led_pin[0] <= 1;
	led_pin[1] <= 0;
	led_pin[2] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
              end
            end 
            if(sw_pin[0] == 1 && sw_pin[1] ==1)
            begin
              if(six_reg == 0)
              begin
              led_pin[0] = 0;
              led_pin[1] = 0;
              led_pin[2] = 0;
              led_pin[5] = 0;
              led_pin[6] = 0;
              led_pin[7] = 0;
              end
              if(six_reg == 1)
              begin
              led_pin[0] = 1;
              led_pin[1] = 1;
              led_pin[2] = 1;
              led_pin[5] = 1;
              led_pin[6] = 1;
              led_pin[7] = 1;
              end
              if(six_reg == 2)
              begin
              led_pin[0] = 0;
              led_pin[1] = 0;
              led_pin[2] = 0;
              led_pin[5] = 0;
              led_pin[6] = 0;
              led_pin[7] = 0;
              end
              if(six_reg == 3)
              begin
              led_pin[0] = 1;
              led_pin[1] = 1;
              led_pin[2] = 1;
              led_pin[5] = 1;
              led_pin[6] = 1;
              led_pin[7] = 1;
              end
              if(six_reg == 4)
              begin
              led_pin[0] = 0;
              led_pin[1] = 0;
              led_pin[2] = 0;
              led_pin[5] = 0;
              led_pin[6] = 0;
              led_pin[7] = 0;
              end
              if(six_reg == 5)
              begin
              led_pin[0] = 1;
              led_pin[1] = 1;
              led_pin[2] = 1;
              led_pin[5] = 1;
              led_pin[6] = 1;
              led_pin[7] = 1;
              end
            end  
    end

endmodule