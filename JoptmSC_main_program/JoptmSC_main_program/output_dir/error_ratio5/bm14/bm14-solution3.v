module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_, new_n5_;
  nand3  g0(.a(x0), .b(x1), .c(x2), .O(new_n4_));
  or2  g1(.a(x0), .b(x2), .O(new_n5_));
  aoi22  g2(.a(x1), .b(x3), .c(new_n4_), .d(new_n5_), .O(z0));
endmodule
