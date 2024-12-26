`timescale 1ns / 1ps

module example_6_4_3(
    input x,
    input y1,y2,y3,
    input rd,
    output reg ny1,ny2,ny3,z
    );
    
    always @(negedge x or negedge rd)                      //行为描述方式

    begin
       if(rd==0)  	                                           	        //  rd=0         n2y=0  ny1=0  z=0
                begin ny3 <= 0; ny2 <= 0; ny1 <= 0; z <= 0; end
       else
                case({y3, y2, y1})
                0:begin ny3<=0;ny2<=0;ny1<=1;z<=0;end
                1:begin ny3<=0;ny2<=1;ny1<=0;z<=0;end
                2:begin ny3<=0;ny2<=1;ny1<=1;z<=0;end
                3:begin ny3<=1;ny2<=0;ny1<=0;z<=0;end
                4:begin ny3<=1;ny2<=0;ny1<=1;z<=0;end
                5:begin ny3<=1;ny2<=1;ny1<=0;z<=0;end
                6:begin ny3<=1;ny2<=1;ny1<=1;z<=0;end
                7:begin ny3<=0;ny2<=0;ny1<=0;z<=1;end
                endcase
    end

endmodule