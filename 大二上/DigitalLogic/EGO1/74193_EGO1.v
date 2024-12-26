//采用行为描述方式实现74193芯片（双时钟4位二进制同步可逆计数器）。该电路的输入D、C、B、A，CLR、/LD，CPu、CPd，输出为QD、QC、QB、QA，/QCC、/QCB。
//输入D、C、B、A为开发板上左边的4个拨动开关，输入CLR、/LD为开发板上右边的2个拨动开关，输入CPu、CPd为开发板上2个按键（EGO1开发板为S4、S1）
//输出QD、QC、QB、QA为开发板上左边的4个LED灯。输出/QCC、/QCB为开发板上右边的2个LED灯。

`timescale 1ns / 1ps	

module ttl74193(						
     input clk,
     input rst,
     input clr, ld,
     input d, c, b, a,
     input cpu, cpd,	
     output qd, qc, qb, qa,
     output qcc, qcb
);

    wire t;
    reg fqcc, fqcb;
    reg [4:0] count;
    reg cpu_curr, cpu_prev;
    reg cpd_curr, cpd_prev;
    reg [19:0] debounce_counter1 = 0; 				//用于cpu的去抖动计数器
    reg [19:0] debounce_counter2 = 0; 				//用于cpd的去抖动计数器

    parameter DEBOUNCE_PERIOD = 10000; 			//去抖动时间长度，根据时钟频率调整

    always @(posedge clk or negedge rst) 			// 消除按键的抖动（去抖动）
    begin
	    if (!rst) 
		begin
		        cpu_curr <= 1;
		        cpu_prev <= 1;
		        debounce_counter1 <= 0;
		        cpd_curr <= 1;
		        cpd_prev <= 1;
		        debounce_counter2 <= 0;
	    	end 
	    else 
		begin

		        cpu_prev <= cpu_curr;
		        if(cpu==cpu_curr)
			begin
			        cpu_curr <= cpu;
		                end
		        else if (cpu != cpu_prev)
			begin
			        if(debounce_counter1 != DEBOUNCE_PERIOD - 1)
				begin
					        debounce_counter1 <= debounce_counter1 + 1;
				end
			        if( debounce_counter1 == DEBOUNCE_PERIOD - 1)
				begin
					        debounce_counter1 <= 0;
				        cpu_curr <= cpu;
				end
			end        
		         cpd_prev <= cpd_curr;
		         if(cpd == cpd_curr)
			begin
			        cpd_curr <= cpd;
		                end
		        else if (cpd != cpd_prev)
		        begin
			         if(debounce_counter2 != DEBOUNCE_PERIOD - 1)
			         	begin
				        debounce_counter2 <= debounce_counter2 + 1;
			        	end
			        if( debounce_counter2 == DEBOUNCE_PERIOD - 1)
			        	begin
				        debounce_counter2 <= 0;
				        cpd_curr <= cpd;
			        	end
		        end 
	             end
    end

    always@(posedge clk or negedge rst)			
    begin
	if(!rst)
		begin
 			count <= 0;
			fqcc <= 1; 
			fqcb <= 1; 		
		end
	else if(clr==1)				
		begin											
 			count <= 0;
			fqcc <= 1; 
			fqcb <= 1; 		
		end
	else if(clr==0 && ld==0)				
		begin	
			count <= 8*d+4*c+2*b+a;
			fqcc <= 1; 
			fqcb <= 1; 		
		end
	else if(clr==0 && ld==1)				
		begin	
                                	if(!cpu_curr && cpu_prev)	
						begin							
							  if(count == 15)
								begin					
									    count <= 0;
									    fqcc <= 0;
									    fqcb <= fqcb;
								end
							  else if(count == 0)
								begin					
									    count <= 1;
									    fqcc <= 1;
									    fqcb <= fqcb;
								end
							  else 
								begin					
									    count <= count + 1;
									    fqcc <= fqcc;
									    fqcb <= fqcb;
								end
						  end
                                	if(!cpd_curr && cpd_prev)	
						begin							
							  if(count == 0)
								begin					
									    count <= 15;
									    fqcb <= 0;
									    fqcc <= fqcc;
								end
							  else if(count == 15)
								begin					
									    count <= 14;
									    fqcb <= 1;
									    fqcc <= fqcc;
								end
							  else 
								begin					
									    count <= count - 1;
									    fqcb <= fqcb;
									    fqcc <= fqcc;
								end
						  end													
		end
	else
		begin					
			count <= count;
			fqcc <= fqcc;
			fqcb <= fqcb;
		end
    end

    assign {t,qd,qc,qb,qa} = count;
    assign qcc = fqcc;
    assign qcb = fqcb;

endmodule

module ttl74193_exe(
    input sys_clk_in,				//系统时钟信号
    input sys_rst_n,				//系统复位键
    input sw_pin[7:0],                               	                //8个拨动开关
    input btn_1, btn_4, 			//2个按键（S1、S4）
    output [15:0] led_pin    		 	//16个led灯            
);

    ttl74193 U(.clk(sys_clk_in), .rst(sys_rst_n), .clr(sw_pin[6]), .ld(sw_pin[7]), .d(sw_pin[0]), .c(sw_pin[1]), .b(sw_pin[2]), .a(sw_pin[3]), .cpu(btn_4), .cpd(btn_1), .qd(led_pin[0]), .qc(led_pin[1]), .qb(led_pin[2]), .qa(led_pin[3]), .qcc(led_pin[6]), .qcb(led_pin[7]));

endmodule




