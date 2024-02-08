module \solution-0 (
  x0, x1, x2, x3, x4,
  z0 );
  input x0, x1, x2, x3, x4;
  output z0;
  wire new_n5_, new_n6_;
  nand3  g0(.a(x1), .b(x2), .c(x4), .O(new_n5_));
  xor2  g1(.a(x0), .b(x1), .O(new_n6_));
  oai22  g2(.a(x2), .b(new_n6_), .c(x3), .d(new_n5_), .O(z0));
endmodule
