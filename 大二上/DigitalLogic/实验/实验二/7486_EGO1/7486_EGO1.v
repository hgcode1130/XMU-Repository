module 7486_EGO1(
    input a1, b1,
    input a2, b2,
    input a3, b3,
    input a4, b4,
    output y1, y2, y3, y4
);

    // 子模块：2 输入异或门（行为描述方式）
    module xor_gate(input in1, input in2, output out);
        reg temp;
        always @(*) begin
            temp = in1 ^ in2;
        end
        assign out = temp;
    end

    xor_gate xor1(a1, b1, y1);
    xor_gate xor2(a2, b2, y2);
    xor_gate xor3(a3, b3, y3);
    xor_gate xor4(a4, b4, y4);

endmodule