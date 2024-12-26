//采用行为描述方式实现74290芯片（二-五-十进制加法计数器）。该芯片的输入为S1、S0，R0A、R0B，R9A、R9B，CPA、CPB；输出为QD、QC、QB、QA。
//输入S1、S0为开发板上最左边的2个拨动开关，R0A、R0B、R9A、R9B为开发板上最右边的4个拨动开关，输入CPA、CPB为开发板上2个按键（EGO1开发板为S4、S1）
//输出QD、QC、QB、QA为开发板上最左边的4个LED灯。

`timescale 1ns / 1ps	

module ttl74290(						
     input clk,
     input rst,
     input s1, s0,
     input r0a, r0b,
     input r9a, r9b,
     input cpa, cpb,	
     output qd, qc, qb, qa
);

    reg fqd, fqc, fqb, fqa;
    reg cpa_curr, cpa_prev;
    reg cpb_curr, cpb_prev;
    reg [19:0] debounce_counter1 = 0; 				//用于cpa的去抖动计数器
    reg [19:0] debounce_counter2 = 0; 				//用于cpb的去抖动计数器

    parameter DEBOUNCE_PERIOD = 10000; 			//去抖动时间长度，根据时钟频率调整

    always @(posedge clk or negedge rst) 			// 消除按键的抖动（去抖动）
    begin
	    if (!rst) 
		begin
		        	cpa_curr <= 1; 
			cpa_prev <= 1; 
			debounce_counter1 <= 0;
		        	cpb_curr <= 1; 
			cpb_prev <= 1; 
			debounce_counter2 <= 0;
	    	end 
	    else 
		begin
		        cpa_prev <= cpa_curr;
		        if(cpa==cpa_curr)
			        cpa_curr <= cpa;
		        else if (cpa != cpa_prev)
			begin
			        if(debounce_counter1!=DEBOUNCE_PERIOD-1)
					debounce_counter1<=debounce_counter1 + 1;
			        if(debounce_counter1==DEBOUNCE_PERIOD-1)
				begin
					debounce_counter1 <= 0; 
					cpa_curr <= cpa;
				end
			end        
		         cpb_prev <= cpb_curr;
		         if(cpb==cpb_curr)
			        cpb_curr <= cpb;
		        else if (cpb != cpb_prev)
		                begin
			         if(debounce_counter2!=DEBOUNCE_PERIOD-1)
				        	debounce_counter2<=debounce_counter2 + 1;
			         if(debounce_counter2==DEBOUNCE_PERIOD-1)
			        	begin
				        	debounce_counter2 <= 0; 
					cpb_curr <= cpb;
			        	end
		                end 
	             end
    end

    always@(posedge clk or negedge rst)			
    begin
	if(!rst)
		begin fqd <= 0; fqc <= 0; fqb <= 0; fqa <= 0; end	
	else if((r0a==1 && r0b==1 && r9a==0) || (r0a==1 && r0b==1 && r9b==0)) 				
		begin fqd <= 0; fqc <= 0; fqb <= 0; fqa <= 0; end	
	else if(r9a==1 && r9b==1)				
		begin fqd <= 1; fqc <= 0; fqb <= 0; fqa <= 1; end	
	else if((r0b==0 && r9b==0) || (r0a==0 && r9a==0) || (r0a==0 && r9b==0) || (r0b==0 && r9a==0)) 				
		begin	
		          if(s1==0 && s0==0)
                                		if(!cpa_curr && cpa_prev)	
					begin	
						if(fqa == 0)
							fqa <= 1;
						else if(fqa == 1)
							fqa <= 0;
					end
		          if(s1==0 && s0==1)
                                		if(!cpb_curr && cpb_prev)
					begin
						if(fqd==0 && fqc==0 && fqb==0)
							begin fqd <= 0; fqc <= 0; fqb <= 1; end	
						else if(fqd==0 && fqc==0 && fqb==1)
							begin fqd <= 0; fqc <= 1; fqb <= 0; end	
						else if(fqd==0 && fqc==1 && fqb==0)
							begin fqd <= 0; fqc <= 1; fqb <= 1; end	
						else if(fqd==0 && fqc==1 && fqb==1)
							begin fqd <= 1; fqc <= 0; fqb <= 0; end	
						else if(fqd==1 && fqc==0 && fqb==0)
							begin fqd <= 0; fqc <= 0; fqb <= 0; end	
						else
							begin fqd <= fqd; fqc <= fqc; fqb <= fqb; end	
					end
		          if(s1==1 && s0==0)
                                		if(!cpa_curr && cpa_prev)
					begin
						if(fqd==0 && fqc==0 && fqb==0 && fqa==0)
							begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=1; end	
						else if(fqd==0 && fqc==0 && fqb==0 && fqa==1)
							begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=0; end	
						else if(fqd==0 && fqc==0 && fqb==1 && fqa==0)
							begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=1; end	
						else if(fqd==0 && fqc==0 && fqb==1 && fqa==1)
							begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=0; end	
						else if(fqd==0 && fqc==1 && fqb==0 && fqa==0)
							begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=1; end	
						else if(fqd==0 && fqc==1 && fqb==0 && fqa==1)
							begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=0; end	
						else if(fqd==0 && fqc==1 && fqb==1 && fqa==0)
							begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=1; end	
						else if(fqd==0 && fqc==1 && fqb==1 && fqa==1)
							begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=0; end	
						else if(fqd==1 && fqc==0 && fqb==0 && fqa==0)
							begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=1; end	
						else if(fqd==1 && fqc==0 && fqb==0 && fqa==1)
							begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=0; end	
						else
							begin fqd <= fqd; fqc <= fqc; fqb <= fqb; fqa <= fqa; end	
					end
		          if(s1==1 && s0==1)
                                		if(!cpb_curr && cpb_prev)	
					begin
						if(fqa==0 && fqd==0 && fqc==0 && fqb==0)
							begin fqa <= 0; fqd <= 0; fqc <= 0; fqb<=1; end	
						else if(fqa==0 && fqd==0 && fqc==0 && fqb==1)
							begin fqa <= 0; fqd <= 0; fqc <= 1; fqb<=0; end	
						else if(fqa==0 && fqd==0 && fqc==1 && fqb==0)
							begin fqa <= 0; fqd <= 0; fqc <= 1; fqb<=1; end	
						else if(fqa==0 && fqd==0 && fqc==1 && fqb==1)
							begin fqa <= 0; fqd <= 1; fqc <= 0; fqb<=0; end	
						else if(fqa==0 && fqd==1 && fqc==0 && fqb==0)
							begin fqa <= 1; fqd <= 0; fqc <= 0; fqb<=0; end	
						else if(fqa==1 && fqd==0 && fqc==0 && fqb==0)
							begin fqa <= 1; fqd <= 0; fqc <= 0; fqb<=1; end	
						else if(fqa==1 && fqd==0 && fqc==0 && fqb==1)
							begin fqa <= 1; fqd <= 0; fqc <= 1; fqb<=0; end	
						else if(fqa==1 && fqd==0 && fqc==1 && fqb==0)
							begin fqa <= 1; fqd <= 0; fqc <= 1; fqb<=1; end	
						else if(fqa==1 && fqd==0 && fqc==1 && fqb==1)
							begin fqa <= 1; fqd <= 1; fqc <= 0; fqb<=0; end	
						else if(fqa==1 && fqd==1 && fqc==0 && fqb==0)
							begin fqa <= 0; fqd <= 0; fqc <= 0; fqb<=0; end	
						else
							begin fqa <= fqa; fqd <= fqd; fqc <= fqc; fqb <= fqb; end	
					end
		end
	else
		begin fqd <= fqd; fqc <= fqc; fqb <= fqb; fqa <= fqa; end	
    end

    assign qd = fqd;
    assign qc = fqc;
    assign qb = fqb;
    assign qa = fqa;

endmodule

module ttl74290_exe(
    input sys_clk_in,				//系统时钟信号
    input sys_rst_n,				//系统复位键
    input sw_pin[7:0],                               	                //8个拨动开关
    input btn_1, btn_4, 			//2个按键（S1、S4）
    output [15:0] led_pin    		 	//16个led灯            
);

    ttl74290 U(.clk(sys_clk_in), .rst(sys_rst_n), .s1(sw_pin[0]), .s0(sw_pin[1]), .r0a(sw_pin[4]), .r0b(sw_pin[5]), .r9a(sw_pin[6]), .r9b(sw_pin[7]), .cpa(btn_4), .cpb(btn_1), .qd(led_pin[0]), .qc(led_pin[1]), .qb(led_pin[2]), .qa(led_pin[3]));

endmodule