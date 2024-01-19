module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_, new_n5_;
  inv1  g0(.a(x1), .O(new_n4_));
  oai22  g1(.a(x0), .b(new_n4_), .c(x2), .d(x3), .O(new_n5_));
  aoi21  g2(.a(x0), .b(x3), .c(new_n5_), .O(z0));
endmodule
