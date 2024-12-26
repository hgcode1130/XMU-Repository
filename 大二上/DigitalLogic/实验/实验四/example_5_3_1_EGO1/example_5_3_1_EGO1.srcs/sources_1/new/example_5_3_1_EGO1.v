`timescale 1ns / 1ps


module example_5_3_1_EGO1(
    input cp,	
    input x1, x2,      
    input rd,                         		 
    input y, yn,			 
    output reg ny, nyn, z 
    );
    
    always @(posedge cp  or negedge rd)                      //行为描述方式

    begin
        if(rd==0)
            begin ny<=0; z=0; end
        else
            case({x1,x2,y})
                0:begin ny<=0;z=0;end
                1:begin ny<=0;z=1;end
                2:begin ny<=0;z=1;end
                3:begin ny<=1;z=0;end
                4:begin ny<=0;z=1;end
                5:begin ny<=1;z=0;end
                6:begin ny<=1;z=0;end
                7:begin ny<=1;z=1;end
            endcase
    end
                                
endmodule
