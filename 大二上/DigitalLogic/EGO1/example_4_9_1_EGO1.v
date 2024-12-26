//采用行为描述方式实现例题4.9的全加器FA电路，输入为开发板上最左边的3个拨动开关，输出为开发板上最左边的2个LED灯。

`timescale 1ns / 1ps	

module example_4_9_1(
    input sw_pin[7:0],            	                   		 //8个拨动开关
    output reg [15:0] led_pin    		 	//16个led灯            
);

    always @(*)					//行为描述方式 
    begin
                case({sw_pin[0],sw_pin[1],sw_pin[2]})
	               0: begin 
			led_pin[0] <= 0;			    		    
			led_pin[1] <= 0;			    	    
		   end
	               1: begin 
			led_pin[0] <= 1;			   
			led_pin[1] <= 0;			    	    
		   end
	               2: begin 
			led_pin[0] <= 1;			
			led_pin[1] <= 0;			    	    
		   end
	               3: begin 
			led_pin[0] <= 0;			
			led_pin[1] <= 1;			    	    
		   end
	               4: begin 
			led_pin[0] <= 1;			
			led_pin[1] <= 0;			    	    
		   end
	               5: begin 
			led_pin[0] <= 0;			 
			led_pin[1] <= 1;			    	    
		   end
	               6: begin 
			led_pin[0] <= 0;			  
			led_pin[1] <= 1;			    	    
		   end
	               7: begin 
			led_pin[0] <= 1;			   
			led_pin[1] <= 1;			    	    		    
		   end
                endcase
    end

endmodule