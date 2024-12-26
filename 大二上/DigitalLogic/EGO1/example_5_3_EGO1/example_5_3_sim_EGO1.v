`timescale 1ns / 1ps

module example_5_3_sim_EGO1;
    reg x1, x2, CP;
    wire y, Z;

    // 实例化被测试的设计模块
    example_5_3_EGO1 dut (
      .x1(x1),
      .x2(x2),
      .CP(CP),
      .y(y),
      .Z(Z)
    );

    initial begin
        // 初始化输入信号
        x1 = 0;
        x2 = 0;
        CP = 0;

        // 等待一段时间，让信号稳定
        #10;

        // 定义输入序列并施加激励
        // 这里可以根据具体需求修改输入序列
        // 以下是一个简单示例，循环施加不同输入值
        repeat(8) begin
            {x1, x2} = $random;
            CP = 1;
            #10;
            CP = 0;
            #10;
        end

        // 仿真结束
        $finish;
    end

endmodule