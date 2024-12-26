//采用行为描述方式实现9.2小节的时序信号发生器电路
//输入为开发板上最左边的拨动开关（/CLR）、按键S4（START）、按键S1（STOP）
//输出为开发板上最左边的LED灯（CP）、最右边的4个LED灯（T1、T2、T3、T4）

`timescale 1ns / 1ps

module example_9_2(
    input sys_clk_in,
    input sys_rst_n,
    input sw_pin[7:0],            	                   		//8个拨动开关
    input btn_1, btn_4,                                        		//S1、S4按键
    output reg [15:0] led_pin    			//16个led灯
);

    reg [24 : 0] cnt_reg; 
    reg [3 : 0] eight_reg;
    reg flag_start;
    reg btn_4_curr, btn_4_prev;
    reg btn_1_curr, btn_1_prev;
    reg [19:0] debounce_counter1 = 0; 				//用于btn_4的去抖动计数器
    reg [19:0] debounce_counter2 = 0; 				//用于btn_1的去抖动计数器
    parameter DEBOUNCE_PERIOD = 10000; 			//去抖动时间长度，根据时钟频率调整

    always @(posedge sys_clk_in or negedge sys_rst_n) 		// 消除按键的抖动（去抖动）
    begin
	    if (!sys_rst_n) 
		begin
		        btn_4_curr <= 1;
		        btn_4_prev <= 1;
		        debounce_counter1 <= 0;
		        btn_1_curr <= 1;
		        btn_1_prev <= 1;
		        debounce_counter2 <= 0;
	    	end 
	    else 
		begin

		        btn_4_prev <= btn_4_curr;
		        if(btn_4==btn_4_curr)
			begin
			        btn_4_curr <= btn_4;
		                end
		        else if (btn_4 != btn_4_prev)
			begin
			        if(debounce_counter1 != DEBOUNCE_PERIOD - 1)
				begin
					        debounce_counter1 <= debounce_counter1 + 1;
				end
			        if( debounce_counter1 == DEBOUNCE_PERIOD - 1)
				begin
					        debounce_counter1 <= 0;
				        btn_4_curr <= btn_4;
				end
			end        
		         btn_1_prev <= btn_1_curr;
		         if(btn_1 == btn_1_curr)
			begin
			        btn_1_curr <= btn_1;
		                end
		        else if (btn_1 != btn_1_prev)
		        begin
			         if(debounce_counter2 != DEBOUNCE_PERIOD - 1)
			         	begin
				        debounce_counter2 <= debounce_counter2 + 1;
			        	end
			        if( debounce_counter2 == DEBOUNCE_PERIOD - 1)
			        	begin
				        debounce_counter2 <= 0;
				        btn_1_curr <= btn_1;
			        	end
		        end 
	             end
    end

    always@(posedge sys_clk_in)		//根据sw_pin[0]拨动开关、S4按键、S1按键，确定LED灯是否闪烁
    begin
        if (!sys_rst_n)
            flag_start <= 0; 
        else
            begin
                if(sw_pin[0] == 1)
                   begin
	    if(!btn_4_curr && btn_4_prev)
		flag_start <= 1;
	    if(!btn_1_curr && btn_1_prev)
		flag_start <= 0;
                  end
                else
                                flag_start <= 0;
            end
    end
		
    always @ (posedge sys_clk_in)		//延时计数
    begin
        if (!sys_rst_n) 
            cnt_reg <= 0; 
        else
            cnt_reg <= cnt_reg + 1;
    end

    always @ (posedge sys_clk_in) 	//eight_reg计数：0-7           最左边的LED不停地闪烁	
    begin
        if (!sys_rst_n)
            eight_reg <= 4'b0000; 
        else if (cnt_reg == 25'h1ffffff) 	//调整 25'h1ffffff 这个值，可以改变LED灯的闪烁时间，值小则闪烁快，值大则闪烁慢
        begin
            if (eight_reg == 4'b1000) 
                eight_reg <= 4'b0000;
            else
                eight_reg <= eight_reg + 1;  	
            led_pin[0] <= ~led_pin[0];	
        end
    end

    always @ (posedge sys_clk_in) 	//4个LED轮流亮
    begin
     if(flag_start == 1)
      begin
        if (eight_reg == 0)
            begin
	led_pin[4] <= 1;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
            end 
        if (eight_reg == 2)
            begin
	led_pin[4] <= 0;
	led_pin[5] <= 1;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
            end 
        if (eight_reg == 4)
            begin
	led_pin[4] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 1;
	led_pin[7] <= 0;
            end 
        if (eight_reg == 6)
            begin
	led_pin[4] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 1;
            end 
      end
    else
      begin
	led_pin[4] <= 0;
	led_pin[5] <= 0;
	led_pin[6] <= 0;
	led_pin[7] <= 0;
      end
    end

endmodule