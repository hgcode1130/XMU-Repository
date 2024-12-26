//采用行为描述方式实现例题4.1的代码转换电路，输入为最左边的4个拨动开关，输出为最左边的4个LED灯。

`timescale 1ns / 1ps	

module example_4_3_1(
    input sw_pin[7:0],            	                   		 //8个拨动开关
    output reg [15:0] led_pin    		 	//16个led灯            
);

always @(*)					//行为描述方式
begin
                case({sw_pin[0],sw_pin[1],sw_pin[2],sw_pin[3]})
	               0: begin 
			led_pin[0] <= 0;			    //  ABCD = 0000        WXYZ = 0011
			led_pin[1] <= 0;			    
			led_pin[2] <= 1;			    
			led_pin[3] <= 1;			    
		   end
	               1: begin 
			led_pin[0] <= 0;			    //  ABCD = 0001        WXYZ = 0100
			led_pin[1] <= 1;			    
			led_pin[2] <= 0;			    
			led_pin[3] <= 0;			    
		   end
	               2: begin 
			led_pin[0] <= 0;			    //  ABCD = 0010        WXYZ = 0101
			led_pin[1] <= 1;			    
			led_pin[2] <= 0;			    
			led_pin[3] <= 1;			    
		   end
	               3: begin 
			led_pin[0] <= 0;			    //  ABCD = 0011        WXYZ = 0110
			led_pin[1] <= 1;			    
			led_pin[2] <= 1;			    
			led_pin[3] <= 0;			    
		   end
	               4: begin 
			led_pin[0] <= 0;			    //  ABCD = 0100        WXYZ = 0111
			led_pin[1] <= 1;			    
			led_pin[2] <= 1;			    
			led_pin[3] <= 1;			    
		   end
	               5: begin 
			led_pin[0] <= 1;			    //  ABCD = 0101        WXYZ = 1000
			led_pin[1] <= 0;			    
			led_pin[2] <= 0;			    
			led_pin[3] <= 0;			    
		   end
	               6: begin 
			led_pin[0] <= 1;			    //  ABCD = 0110        WXYZ = 1001
			led_pin[1] <= 0;			    
			led_pin[2] <= 0;			    
			led_pin[3] <= 1;			    
		   end
	               7: begin 
			led_pin[0] <= 1;			    //  ABCD = 0111        WXYZ = 1010
			led_pin[1] <= 0;			    
			led_pin[2] <= 1;			    
			led_pin[3] <= 0;			    
		   end
	               8: begin 
			led_pin[0] <= 1;			    //  ABCD = 1000        WXYZ = 1011
			led_pin[1] <= 0;			    
			led_pin[2] <= 1;			    
			led_pin[3] <= 1;			    
		   end
	               9: begin 
			led_pin[0] <= 1;			    //  ABCD = 1001        WXYZ = 1100
			led_pin[1] <= 1;			    
			led_pin[2] <= 0;			    
			led_pin[3] <= 0;			    
		   end
                endcase
end

endmodule