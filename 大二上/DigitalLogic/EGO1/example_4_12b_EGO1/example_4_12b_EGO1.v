module blood_compatibility_structural(
    input donor_type1,
    input donor_type0,
    input recipient_type1,
    input recipient_type0,
    output compatibility
);

// 内部信号声明
wire w1, w2, w3, w4;

// 使用与门、或门和非门实现逻辑
and u1(w1, donor_type1, recipient_type1);
and u2(w2, donor_type1, recipient_type0);
and u3(w3, donor_type0, recipient_type1);
and u4(w4, donor_type0, recipient_type0);
or u5(compatibility, w1, w2, w3, w4);

endmodule

module top_module(
    input [3:0] switches,
    output led
);

blood_compatibility_structural uut(
  .donor_type1(switches[3]),
  .donor_type0(switches[2]),
  .recipient_type1(switches[1]),
  .recipient_type0(switches[0]),
  .compatibility(led)
);

endmodule