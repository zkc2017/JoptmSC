module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_, new_n5_, new_n6_;
  aoi22  g0(.a(x0), .b(x3), .c(x1), .d(x2), .O(new_n4_));
  nor2  g1(.a(x1), .b(x2), .O(new_n5_));
  oai22  g2(.a(x0), .b(x3), .c(new_n4_), .d(new_n5_), .O(new_n6_));
  xor2  g3(.a(new_n5_), .b(new_n6_), .O(z0));
endmodule
