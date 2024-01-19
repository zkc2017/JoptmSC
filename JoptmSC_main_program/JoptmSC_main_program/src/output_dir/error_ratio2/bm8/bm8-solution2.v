module \solution-0 (
  x0, x1, x2, x3, x4, x5,
  z0 );
  input x0, x1, x2, x3, x4, x5;
  output z0;
  wire new_n6_, new_n7_;
  nand3  g0(.a(x3), .b(x4), .c(x5), .O(new_n6_));
  nand2  g1(.a(x2), .b(x4), .O(new_n7_));
  aoi22  g2(.a(x0), .b(new_n6_), .c(x1), .d(new_n7_), .O(z0));
endmodule
