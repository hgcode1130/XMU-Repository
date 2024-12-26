module example_5_3_EGO1 (
    input x1,
    input x2,
    input CP,
    inout y,
    output Z
);
    wire s1, s2, s3;

    // 实例化D触发器模块
    d_ff dff1 (
      .D(s1),
      .CP(CP),
      .CI(1'b0),
      .ID(y),
      .Q(s2)
    );

    assign s1 = x1 ^ x2 ^ y;
    assign s3 = s2 & (x1 ^ x2);
    assign Z = s3;
endmodule

// D触发器模块定义
module d_ff (
    input D,
    input CP,
    input CI,
    inout ID,
    output reg Q
);
    always @(posedge CP) begin
        if (CI)
            Q <= 1'b1;
        else
            Q <= D;
        ID <= D;
    end
endmodule