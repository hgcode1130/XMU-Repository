`timescale 1ns / 1ps

// 模块1：数码管扫描与译码驱动 
module number(
    input           clk,
    input           rst,
    input   [31:0]  data,      // 接收 HH-MM-SS 的数据
    output reg[7:0] seg_data,  // 段选 (a,b,c,d,e,f,g,dp)
    output reg[7:0] seg_cs     // 位选 (AN7-AN0)
    );

    reg clk_scan;     
    integer clk_cnt;
    reg [2:0] scan_idx;        // 0-7 扫描索引
    reg [3:0] hex_in;          // 当前要显示的4位数字

    // 生成扫描时钟 (约1kHz)
    always @(posedge clk or negedge rst) begin
        if(!rst) begin
            clk_scan <= 0;
            clk_cnt <= 0;
        end else begin
            if(clk_cnt >= 50_000) begin // 100MHz / 50000 * 2 = 1kHz
                clk_cnt <= 0;
                clk_scan <= ~clk_scan;
            end else begin
                clk_cnt <= clk_cnt + 1;
            end
        end
    end
    
    // 扫描位选逻辑
    always @(posedge clk_scan or negedge rst) begin
        if(!rst) 
            scan_idx <= 0;
        else 
            scan_idx <= scan_idx + 1;
    end

    // 位选输出 (EGO1 通常位选也是低电平有效，这里生成独热码的反码)
    always @(*) begin
        case(scan_idx)
            3'd0: begin seg_cs = 8'b1111_1110; hex_in = data[3:0];   end // 秒个位
            3'd1: begin seg_cs = 8'b1111_1101; hex_in = data[7:4];   end // 秒十位
            3'd2: begin seg_cs = 8'b1111_1011; hex_in = data[11:8];  end // -
            3'd3: begin seg_cs = 8'b1111_0111; hex_in = data[15:12]; end // 分个位
            3'd4: begin seg_cs = 8'b1110_1111; hex_in = data[19:16]; end // 分十位
            3'd5: begin seg_cs = 8'b1101_1111; hex_in = data[23:20]; end // -
            3'd6: begin seg_cs = 8'b1011_1111; hex_in = data[27:24]; end // 时个位
            3'd7: begin seg_cs = 8'b0111_1111; hex_in = data[31:28]; end // 时十位
            default: begin seg_cs = 8'b1111_1111; hex_in = 4'hF; end
        endcase
    end

    // 段码译码
    always @(*) begin
        case(hex_in)
            4'h0: seg_data = 8'hC0; // 0 (1100 0000)
            4'h1: seg_data = 8'hF9; // 1
            4'h2: seg_data = 8'hA4; // 2
            4'h3: seg_data = 8'hB0; // 3
            4'h4: seg_data = 8'h99; // 4
            4'h5: seg_data = 8'h92; // 5
            4'h6: seg_data = 8'h82; // 6
            4'h7: seg_data = 8'hF8; // 7
            4'h8: seg_data = 8'h80; // 8
            4'h9: seg_data = 8'h90; // 9
            4'hf: seg_data = 8'hBF; // - (Dash, 1011 1111)
            default: seg_data = 8'hFF; // 全灭
        endcase
    end

endmodule

// 模块2：按键消抖 
module btn_debounce(
    input clk,
    input rst_n,
    input btn_in,
    output reg btn_posedge // 按键按下的瞬间产生一个脉冲
    );
    reg [19:0] cnt;
    reg btn_prev;
    reg btn_curr;

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            cnt <= 0;
            btn_curr <= 0;
            btn_prev <= 0;
            btn_posedge <= 0;
        end else begin
            btn_prev <= btn_curr; // 保存上一次状态
            
            // 简单的消抖逻辑
            if(cnt < 20'd999_999) begin // 10ms
                 if(btn_in == 1'b1) cnt <= cnt + 1;
                 else cnt <= 0;
            end 
            else begin
                 btn_curr <= 1'b1; // 确认按下
                 cnt <= 0;         // 清零等待松开（这里简化处理）
            end
            
            // 松开检测
            if(btn_in == 0) begin
                cnt <= 0;
                btn_curr <= 0;
            end

            // 产生上升沿脉冲
            btn_posedge <= (~btn_prev) & btn_curr;
        end
    end
endmodule

// 模块3：顶层时钟逻辑
module E_CLOCK(
    input   sys_clk_in,
    input   sys_rst_n,
    input   [4:0] btn,          // 新增：5个按键输入 (S4, S3, S2, S1, S0)
    output  [7:0] seg_data_pin, // 数码管段
    output  [7:0] seg_cs_pin    // 数码管位
    );

    integer timer_cnt;
    reg [5:0] seconds;
    reg [5:0] minutes;
    reg [5:0] hours;
    reg [31:0] display_data;

    // 按键脉冲信号
    wire btn4_pulse, btn3_pulse, btn2_pulse, btn1_pulse; // S0通常直接做复位，或者这里也可以消抖
    
    // 实例化消抖模块
    btn_debounce u_btn4 (.clk(sys_clk_in), .rst_n(sys_rst_n), .btn_in(btn[4]), .btn_posedge(btn4_pulse)); // S4: 小时+
    btn_debounce u_btn3 (.clk(sys_clk_in), .rst_n(sys_rst_n), .btn_in(btn[3]), .btn_posedge(btn3_pulse)); // S3: 分钟+
    btn_debounce u_btn2 (.clk(sys_clk_in), .rst_n(sys_rst_n), .btn_in(btn[2]), .btn_posedge(btn2_pulse)); // S2: 秒清零

    // 时间计数与调整逻辑
    always @(posedge sys_clk_in or negedge sys_rst_n) begin
        if(!sys_rst_n) begin
            timer_cnt <= 0;
            seconds <= 0;
            minutes <= 0;
            hours <= 0;
        end
        else begin
            // --- S4: 调整小时 ---
            if(btn4_pulse) begin
                if(hours >= 23) hours <= 0;
                else hours <= hours + 1;
            end
            
            // --- S3: 调整分钟 ---
            else if(btn3_pulse) begin
                if(minutes >= 59) minutes <= 0;
                else minutes <= minutes + 1;
            end

            // --- S2: 秒归零 ---
            else if(btn2_pulse) begin
                seconds <= 0;
                timer_cnt <= 0; // 重置秒计数器
            end
            
            // --- 正常走时 ---
            else if(timer_cnt >= 100_000_000 - 1) begin
                timer_cnt <= 0;
                if(seconds >= 59) begin
                    seconds <= 0;
                    if(minutes >= 59) begin
                        minutes <= 0;
                        if(hours >= 23) hours <= 0;
                        else hours <= hours + 1;
                    end
                    else minutes <= minutes + 1;
                end
                else seconds <= seconds + 1;
            end
            else begin
                timer_cnt <= timer_cnt + 1;
            end
        end
    end

    // 组合数据用于显示
    // 格式: HH-MM-SS，中间用 F 代表横杠
    always @(*) begin
        display_data[31:28] = hours / 10;
        display_data[27:24] = hours % 10;
        display_data[23:20] = 4'hf;       // 显示 -
        display_data[19:16] = minutes / 10;
        display_data[15:12] = minutes % 10;
        display_data[11:8]  = 4'hf;       // 显示 -
        display_data[7:4]   = seconds / 10;
        display_data[3:0]   = seconds % 10;
    end
    
    // 实例化显示模块
    number U1(
        .clk(sys_clk_in),
        .rst(sys_rst_n),
        .data(display_data),
        .seg_data(seg_data_pin),
        .seg_cs(seg_cs_pin)
    );

endmodule