//������Ϊ������ʽʵ������4.9��ȫ����FA��·������Ϊ������������ߵ�3���������أ����Ϊ������������ߵ�2��LED�ơ�

`timescale 1ns / 1ps	

module example_4_9_1(
    input sw_pin[7:0],            	                   		 //8����������
    output reg [15:0] led_pin    		 	//16��led��            
);

    always @(*)					//��Ϊ������ʽ 
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