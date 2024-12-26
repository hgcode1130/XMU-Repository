module blood_compatibility_behavioral(
    input donor_type1,
    input donor_type0,
    input recipient_type1,
    input recipient_type0,
    output reg compatibility
);

always @(*) begin
    case ({donor_type1, donor_type0})
        2'b00: begin
            case ({recipient_type1, recipient_type0})
                2'b00: compatibility = 1;
                2'b01: compatibility = 1;
                2'b10: compatibility = 1;
                2'b11: compatibility = 1;
            endcase
        end
        2'b01: begin
            case ({recipient_type1, recipient_type0})
                2'b01: compatibility = 1;
                2'b11: compatibility = 1;
                default: compatibility = 0;
            endcase
        end
        2'b10: begin
            case ({recipient_type1, recipient_type0})
                2'b10: compatibility = 1;
                2'b11: compatibility = 1;
                default: compatibility = 0;
            endcase
        end
        2'b11: begin
            case ({recipient_type1, recipient_type0})
                2'b11: compatibility = 1;
                default: compatibility = 0;
            endcase
        end
    endcase
end

endmodule

module top_module(
    input [3:0] switches,
    output led
);

blood_compatibility_behavioral uut(
  .donor_type1(switches[3]),
  .donor_type0(switches[2]),
  .recipient_type1(switches[1]),
  .recipient_type0(switches[0]),
  .compatibility(led)
);

endmodule