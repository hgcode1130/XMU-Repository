`timescale 1ns / 1ps

module example_5_3_sim_EGO1;
    reg x1, x2, CP;
    wire y, Z;

    // ʵ���������Ե����ģ��
    example_5_3_EGO1 dut (
      .x1(x1),
      .x2(x2),
      .CP(CP),
      .y(y),
      .Z(Z)
    );

    initial begin
        // ��ʼ�������ź�
        x1 = 0;
        x2 = 0;
        CP = 0;

        // �ȴ�һ��ʱ�䣬���ź��ȶ�
        #10;

        // �����������в�ʩ�Ӽ���
        // ������Ը��ݾ��������޸���������
        // ������һ����ʾ����ѭ��ʩ�Ӳ�ͬ����ֵ
        repeat(8) begin
            {x1, x2} = $random;
            CP = 1;
            #10;
            CP = 0;
            #10;
        end

        // �������
        $finish;
    end

endmodule