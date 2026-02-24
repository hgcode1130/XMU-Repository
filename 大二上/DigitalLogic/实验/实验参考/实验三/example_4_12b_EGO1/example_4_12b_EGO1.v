module blood_compatibility_structural(
    input donor_type1,
    input donor_type0,
    input recipient_type1,
    input recipient_type0,
    output compatibility
);

wire w1, w2, w3, w4;

not u1(w1,donor_type0);
not u2(w2,donor_type1);
nor u3(w3,recipient_type0,w1);
nor u4(w4,recipient_type1,w2);
nor u5(compatibility,w3,w4);

endmodule

module top_module(
    input [7:0] sw_pin,   
    output [15:0] led_pin 
);

blood_compatibility_structural uut(
  .donor_type1(sw_pin[1]),
  .donor_type0(sw_pin[0]),
  .recipient_type1(sw_pin[7]),
  .recipient_type0(sw_pin[6]),
  .compatibility(led_pin[0])
);

endmodule