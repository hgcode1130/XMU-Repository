//������Ϊ������ʽʵ��9.4С�ڵ�����β�ƿ�������·
//����Ϊ������������ߵ�2���������أ�K1��K0��
//���Ϊ������������ߵ�3��LED�ƣ�L1��L2��L3�������ұߵ�3��LED�ƣ�R1��R2��R3��

`timescale 1ns / 1ps

module example_9_4(
    input sys_clk_in,
    input sys_rst_n,
    input sw_pin[7:0],            	                   		//8����������
    output reg [15:0] led_pin    			//16��led��
);

    reg [24 : 0] cnt_reg; 
    reg [2 : 0] six_reg;
		
    always @ (posedge sys_clk_in)		//��ʱ����
    begin
        if (!sys_rst_n) 
            cnt_reg <= 0; 
        else
            cnt_reg <= cnt_reg + 1;
    end

    always @ (posedge sys_clk_in) 	//six_reg������0-5           
    begin
        if (!sys_rst_n)
            six_reg <= 3'b000; 
        else if (cnt_reg == 25'h1ffffff) 	//���� 25'h1ffffff ���ֵ�����Ըı�LED�Ƶ���˸ʱ�䣬ֵС����˸�죬ֵ������˸��
        begin
            if (six_reg == 3'b110) 
                six_reg <= 3'b000;
            else
                six_reg <= six_reg + 1;  	
        end
    end

    always @ (posedge sys_clk_in) 	//6��LED������
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