module \solution-0 (
  x0, x1, x2, x3, x4, x5,
  z0 );
  input x0, x1, x2, x3, x4, x5;
  output z0;
  wire new_n6_, new_n7_;
  aoi21  g0(.a(x3), .b(x5), .c(x0), .O(new_n6_));
  aoi21  g1(.a(x1), .b(x4), .c(new_n6_), .O(new_n7_));
  or2  g2(.a(x2), .b(new_n7_), .O(z0));
endmodule
