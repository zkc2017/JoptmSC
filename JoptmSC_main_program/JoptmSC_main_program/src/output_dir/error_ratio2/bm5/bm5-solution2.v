module \solution-0 (
  x0, x1, x2, x3, x4,
  z0 );
  input x0, x1, x2, x3, x4;
  output z0;
  wire new_n5_, new_n6_;
  inv1  g0(.a(x0), .O(new_n5_));
  aoi22  g1(.a(x0), .b(x4), .c(x1), .d(x3), .O(new_n6_));
  aoi21  g2(.a(x2), .b(new_n5_), .c(new_n6_), .O(z0));
endmodule
