`timescale 1ns / 1ps

module flowing_light(
    input sys_clk_in,
    input sys_rst_n,
    output [15:0] led_pin    		//ÓµÓÐ16¸öled_pinµÆ
);
    reg [23 : 0] cnt_reg; 
    reg [15 : 0] light_reg;

    always @ (posedge sys_clk_in)
    begin
        if (!sys_rst_n) 
            cnt_reg <= 0; 
        else
            cnt_reg <= cnt_reg + 1;
    end

    always @ (posedge sys_clk_in) 
    begin
        if (!sys_rst_n)
            light_reg <= 16'h0001; 
        else if (cnt_reg == 24'hffffff) 
        begin
            if (light_reg == 16'h8000) 
                light_reg <= 16'h0001;
            else
                light_reg <= light_reg << 1;  		//×óÒÆ
        end
    end

    assign led_pin = light_reg; 

endmodule