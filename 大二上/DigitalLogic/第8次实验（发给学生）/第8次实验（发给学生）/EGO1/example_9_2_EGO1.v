//������Ϊ������ʽʵ��9.2С�ڵ�ʱ���źŷ�������·
//����Ϊ������������ߵĲ������أ�/CLR��������S4��START��������S1��STOP��
//���Ϊ������������ߵ�LED�ƣ�CP�������ұߵ�4��LED�ƣ�T1��T2��T3��T4��

`timescale 1ns / 1ps

module example_9_2(
    input sys_clk_in,
    input sys_rst_n,
    input sw_pin[7:0],            	                   		//8����������
    input btn_1, btn_4,                                        		//S1��S4����
    output reg [15:0] led_pin    			//16��led��
);

    reg [24 : 0] cnt_reg; 
    reg [3 : 0] eight_reg;
    reg flag_start;
    reg btn_4_curr, btn_4_prev;
    reg btn_1_curr, btn_1_prev;
    reg [19:0] debounce_counter1 = 0; 				//����btn_4��ȥ����������
    reg [19:0] debounce_counter2 = 0; 				//����btn_1��ȥ����������
    parameter DEBOUNCE_PERIOD = 10000; 			//ȥ����ʱ�䳤�ȣ�����ʱ��Ƶ�ʵ���

    always @(posedge sys_clk_in or negedge sys_rst_n) 		// ���������Ķ�����ȥ������
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

    always@(posedge sys_clk_in)		//����sw_pin[0]�������ء�S4������S1������ȷ��LED���Ƿ���˸
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
		
    always @ (posedge sys_clk_in)		//��ʱ����
    begin
        if (!sys_rst_n) 
            cnt_reg <= 0; 
        else
            cnt_reg <= cnt_reg + 1;
    end

    always @ (posedge sys_clk_in) 	//eight_reg������0-7           ����ߵ�LED��ͣ����˸	
    begin
        if (!sys_rst_n)
            eight_reg <= 4'b0000; 
        else if (cnt_reg == 25'h1ffffff) 	//���� 25'h1ffffff ���ֵ�����Ըı�LED�Ƶ���˸ʱ�䣬ֵС����˸�죬ֵ������˸��
        begin
            if (eight_reg == 4'b1000) 
                eight_reg <= 4'b0000;
            else
                eight_reg <= eight_reg + 1;  	
            led_pin[0] <= ~led_pin[0];	
        end
    end

    always @ (posedge sys_clk_in) 	//4��LED������
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