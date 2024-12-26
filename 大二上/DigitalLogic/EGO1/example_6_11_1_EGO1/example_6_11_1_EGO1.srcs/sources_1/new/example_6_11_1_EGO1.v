`timescale 1ns / 1ps	

module example_6_11_1(
    input x2, x1,                               		 
    input y2, y1,				
    output reg ny2, ny1, z    		 	        
);

    always @(*)                      //行为描述方式
    begin
	if(x2==0 & x1==0) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 00       z=0
	                1: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 00       z=0
	                2: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 00       z=1
	                3: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 00       z=0
                        endcase
                end

	if(x2==0 & x1==1) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 01       z=0
	                1: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 01       z=0
	                2: begin ny2 <= 0; ny1 <= 1; z <= 1; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 01       z=1
	                3: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 01       z=0
                        endcase
                end

	if(x2==1 & x1==1) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 01       z=0
	                1: begin ny2 <= 0; ny1 <= 1; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 01       z=0
	                2: begin ny2 <= 1; ny1 <= 1; z <= 1; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 11       z=1
	                3: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 11       z=0
                        endcase
                end

	if(x2==1 & x1==0) begin
                        case({y2, y1})
	                0: begin ny2 <= 0; ny1 <= 0; z <= 0; end			      //  y2 y1 = 00       y2n+1 y1n+1 = 10       z=0
	                1: begin ny2 <= 1; ny1 <= 1; z <= 0; end			      //  y2 y1 = 01       y2n+1 y1n+1 = 01       z=0
	                2: begin ny2 <= 1; ny1 <= 0; z <= 1; end			      //  y2 y1 = 11       y2n+1 y1n+1 = 01       z=1
	                3: begin ny2 <= 1; ny1 <= 0; z <= 0; end			      //  y2 y1 = 10       y2n+1 y1n+1 = 10       z=0
                        endcase
                end
    end

endmodule

module example_6_11_1_EGO1(   
    input btn_1,
    input sys_clk_in,                              		 	//8个拨动开关
    output [15:0] led_pin 
    );
     reg y2,y1;
    example_6_11_1 U(.x1(btn_1),.x2(sys_clk_in),.y2(y2),.y1(y1),.ny2(led_pin[0]),.ny1(led_pin[1]),.z(led_pin[7]));
    
    initial begin
        y2=0;
        y1=0;
    end
    always @(*)                     		//行为描述方式
    begin
	y2 <= led_pin[0];
	y1 <= led_pin[1];
    end
endmodule
