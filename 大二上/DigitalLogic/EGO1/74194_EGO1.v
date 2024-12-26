//采用行为描述方式实现74194芯片（4位双向移位寄存器）。该芯片的输入为S1、S0，/CLR，DR、DL，CP，D、C、B、A，输出为QD、QC、QB、QA。
//输入DL、DR为开发板上最左、最右2个拨动开关，输入/CLR为开发板上左数第3个拨动开关，输入S1、S0为开发板上左数第5、6个拨动开关，输入D、C、B、A为开发板上左边的4个DIP开关，输入CP为开发板上1个按键（EGO1开发板为S1）。
//输出QD、QC、QB、QA为开发板上左边的4个LED灯。

`timescale 1ns / 1ps	

module ttl74194(						
     input clk,
     input rst,
     input s1, s0,
     input clr,
     input dr, dl,
     input cpa, cpb,	
     input d, c, b, a,	
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
	else if(clr==0) 				
		begin fqd <= 0; fqc <= 0; fqb <= 0; fqa <= 0; end	
	else if(clr==1)
	     	begin
			if(s1==1 && s0==1)
				if(!cpa_curr && cpa_prev)					
					begin fqd <= d; fqc <= c; fqb <= b; fqa <= a; end	
			if(s1==0 && s0==1) 
				begin
					if(dr==0)				
			                                	if(!cpa_curr && cpa_prev)	
							begin	
								if(fqd==0 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=0; end	
								if(fqd==0 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=0; end	
								if(fqd==0 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=1; end	
								if(fqd==0 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=1; end	
								if(fqd==0 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=0; end	
								if(fqd==0 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=0; end	
								if(fqd==0 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=1; end	
								if(fqd==0 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=1; end	
								if(fqd==1 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=0; end	
								if(fqd==1 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=0; end	
								if(fqd==1 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=1; end	
								if(fqd==1 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=1; end	
							end
					if(dr==1)				
			                                	if(!cpa_curr && cpa_prev)	
							begin	
								if(fqd==0 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=0; end	
								if(fqd==0 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=0; end	
								if(fqd==0 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=1; end	
								if(fqd==0 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=1; end	
								if(fqd==0 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=0; end	
								if(fqd==0 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=0; end	
								if(fqd==0 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=1; end		
								if(fqd==0 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=1; end
								if(fqd==1 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=0; end	
								if(fqd==1 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=0; end	
								if(fqd==1 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=1; end	
								if(fqd==1 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=1; end
							end
				end
			if(s1==1 && s0==0) 
				begin
					if(dl==0)				
			                                	if(!cpa_curr && cpa_prev)	
							begin	
								if(fqd==0 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=0; end	
								if(fqd==0 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=0; end	
								if(fqd==0 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=0; end		
								if(fqd==0 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=0; end	
								if(fqd==0 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=0; end					
								if(fqd==0 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=0; end			
								if(fqd==0 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=0; end	
								if(fqd==0 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=0; end			
								if(fqd==1 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=0; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=0; end	
								if(fqd==1 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=0; end		
								if(fqd==1 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=0; end	
								if(fqd==1 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=0; end	
							end
					if(dl==1)				
			                                	if(!cpa_curr && cpa_prev)	
							begin	
								if(fqd==0 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=1; end	

								if(fqd==0 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=1; end	
								if(fqd==0 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==0 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=1; end	
								if(fqd==0 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=1; end	
								if(fqd==0 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=1; end	
								if(fqd==0 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==0 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=1; end	
								if(fqd==1 && fqc==0 && fqb==0 && fqa==0)
									begin fqd <= 0; fqc <= 0; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==0 && fqb==0 && fqa==1)
									begin fqd <= 0; fqc <= 0; fqb <= 1; fqa<=1; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==0)
									begin fqd <= 0; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==0 && fqb==1 && fqa==1)
									begin fqd <= 0; fqc <= 1; fqb <= 1; fqa<=1; end		
								if(fqd==1 && fqc==1 && fqb==0 && fqa==0)
									begin fqd <= 1; fqc <= 0; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==1 && fqb==0 && fqa==1)
									begin fqd <= 1; fqc <= 0; fqb <= 1; fqa<=1; end	
								if(fqd==1 && fqc==1 && fqb==1 && fqa==0)
									begin fqd <= 1; fqc <= 1; fqb <= 0; fqa<=1; end	
								if(fqd==1 && fqc==1 && fqb==1 && fqa==1)
									begin fqd <= 1; fqc <= 1; fqb <= 1; fqa<=1; end	
							end
				end
			if(s1==0 && s0==0) 				
				begin fqd <= fqd; fqc <= fqc; fqb <= fqb; fqa <= fqa; end	
		end
	else
		begin fqd <= fqd; fqc <= fqc; fqb <= fqb; fqa <= fqa; end	
    end

    assign qd = fqd;
    assign qc = fqc;
    assign qb = fqb;
    assign qa = fqa;

endmodule

module ttl74194_exe(
    input sys_clk_in,				//系统时钟信号
    input sys_rst_n,				//系统复位键
    input sw_pin[7:0],                               	                //8个拨动开关
    input dip_pin[7:0],                               	//8个DIP开关
    input btn_1, btn_4, 			//1个按键（S1）
    output [15:0] led_pin    		 	//16个led灯            
);

    ttl74194 U(.clk(sys_clk_in), .rst(sys_rst_n), .s1(sw_pin[4]), .s0(sw_pin[5]), .clr(sw_pin[2]), .dr(sw_pin[7]), .dl(sw_pin[0]), .cpa(btn_1), .cpb(btn_1), .d(dip_pin[0]), .c(dip_pin[1]), .b(dip_pin[2]), .a(dip_pin[3]), .qd(led_pin[0]), .qc(led_pin[1]), .qb(led_pin[2]), .qa(led_pin[3]));

endmodule