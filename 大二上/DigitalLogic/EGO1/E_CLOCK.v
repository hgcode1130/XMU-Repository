`timescale 1ns / 1ps

module number(
    input   clk,rst,
    input   [31:0]data,
    output reg[7:0]seg_data,
    output reg[7:0]seg_data2,
    output reg[7:0]seg_cs,
    output  reg[5:0]led1
    );
    reg clk_500hz;
    integer clk_cnt;
    always @(posedge clk or negedge rst) 
        begin
        if(!rst)
            begin
            clk_500hz<=0;
            clk_cnt<=0;
            end
        else
            begin
            if(clk_cnt>=100_000)
                begin
                clk_cnt<=0;
                clk_500hz<=~clk_500hz;
                end
            else
                begin
                clk_cnt<=clk_cnt+1;
                end
            end
        end
    
    always @(posedge clk_500hz or negedge rst) 
        begin
        if(!rst) seg_cs<=8'b00000001;
        else    seg_cs<={seg_cs[6:0],seg_cs[7]};
        end

    reg[7:0]dis_data;
    always @(seg_cs) 
        begin
        case(seg_cs)
        8'b10000000:dis_data=data[3:0];
        8'b01000000:dis_data=data[7:4];
        8'b00100000:dis_data=data[11:8];
        8'b00010000:dis_data=data[15:12];
        8'b00001000:dis_data=data[19:16];
        8'b00000100:dis_data=data[23:20];
        8'b00000010:dis_data=data[27:24];
        8'b00000001:dis_data=data[31:28];
        default:dis_data=4'hf;
        endcase
        end

    // reg [7:0] seg_data; 
    always @(dis_data )
        begin
        case(dis_data )
        04'h0: seg_data = 8'h3F;
        04'h1: seg_data = 8'h06;
        04'h2: seg_data = 8'h5B;
        04'h3: seg_data = 8'h4F;
        04'h4: seg_data = 8'h66;
        04'h5: seg_data = 8'h6D;
        04'h6: seg_data = 8'h7D;
        04'h7: seg_data = 8'h07;
        04'h8: seg_data = 8'h7F;
        04'h9: seg_data = 8'h6F;
        04'ha: seg_data = 8'h77;
        04'hb: seg_data = 8'h7C;
        04'hc: seg_data = 8'h39;
        04'hd: seg_data = 8'h5E;
        04'he: seg_data = 8'h76;   //79æ”?76Hå?
        04'hf: seg_data = 8'h40;   //71æ”?40-å?
        default: seg_data = 8'h40;
        endcase
        case(dis_data )
        04'h0: seg_data2 = 8'h3F;
        04'h1: seg_data2 = 8'h06;
        04'h2: seg_data2 = 8'h5B;
        04'h3: seg_data2 = 8'h4F;
        04'h4: seg_data2 = 8'h66;
        04'h5: seg_data2 = 8'h6D;
        04'h6: seg_data2 = 8'h7D;
        04'h7: seg_data2 = 8'h07;
        04'h8: seg_data2 = 8'h7F;
        04'h9: seg_data2 = 8'h6F;
        04'ha: seg_data2 = 8'h77;
        04'hb: seg_data2 = 8'h7C;
        04'hc: seg_data2 = 8'h39;
        04'hd: seg_data2 = 8'h5E;
        04'he: seg_data2 = 8'h76;   //79æ”?76Hå?
        04'hf: seg_data2 = 8'h40;   //71æ”?40-å?
        default: seg_data2 = 8'h40;
        endcase
        end

endmodule

module E_CLOCK(
    input   sys_clk_in,
    input   sys_rst_n,
    output  [7:0]seg_data_0_pin,
    output  [7:0]seg_data_1_pin,
    output  [7:0]seg_cs_pin
    );

    integer timer_cnt;
    reg [6:0]seconds;
    reg [6:0]minutes;
    reg [5:0]hours;

    always @(posedge sys_clk_in or negedge sys_rst_n) begin
        if(!sys_rst_n)
            begin
            timer_cnt <= 0;
            seconds <= 0;
            minutes <= 0;
            hours <= 0;
            end
        else if(timer_cnt>=100_000_000)
            begin
            timer_cnt<=0;
            if(seconds>=59)     
                begin
                seconds<=0;
                if(minutes>=59)     
                    begin
                    minutes<=0;
                    if(hours>=23)     
                        begin
                        hours<=0;
                        end
                    else    hours<=hours+1;
                    end
                else    minutes<=minutes+1;
                end
            else    seconds<=seconds+1;
            end
        else    timer_cnt <= timer_cnt+1;
    end

    reg [31:0] data;
    always @(seconds) begin
        data[31:28] = hours/10;
        data[27:24] = hours%10;
        data[23:20] = 04'hf;
        data[19:16] = minutes/10;
        data[15:12] = minutes%10;
        data[11:8]  = 04'hf;
        data[7:4]   = seconds/10;
        data[3:0]   = seconds%10;
    end
    

    number U1(.clk(sys_clk_in),.rst(sys_rst_n),.data(data),.seg_data(seg_data_0_pin),.seg_data2(seg_data_1_pin),.seg_cs(seg_cs_pin));

endmodule