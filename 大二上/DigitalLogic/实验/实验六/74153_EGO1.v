`timescale 1ns / 1ps	

module ttl74153(
    input d0, d1, d2, d3, a1, a0, g,                         		 
    output y    	
);
    reg f;


    always @(*)                        //琛屼负鎻忚堪鏂瑰紡
    begin
          if(g==1)
                begin f <= 0; end
          else
                if(a1==0&a0==0)
                    begin f <= d0; end
                if(a1==0&a0==1)
                    begin f <= d1; end
                if(a1==1&a0==0)
                    begin f <= d2; end
                if(a1==1&a0==1)
                    begin f <= d3; end
           
    end

    assign y = f;
    

endmodule

module ttl74153_exe(
    input sw_pin[0:7],                               		 	//8个拨动开关
    output [15:0] led_pin    		 		//16个led灯            
);
    
    ttl74153 U(.d0(sw_pin[4]),.d1(sw_pin[5]),.d2(sw_pin[6]),.d3(sw_pin[7]),.a1(sw_pin[1]),.a0(sw_pin[2]),.g(sw_pin[0]),.y(led_pin[0]));

endmodule