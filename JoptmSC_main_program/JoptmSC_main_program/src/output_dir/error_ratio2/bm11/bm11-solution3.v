module \solution-0 (
  x0, x1, x2, x3, x4, x5,
  z0 );
  input x0, x1, x2, x3, x4, x5;
  output z0;
  wire new_n6_, new_n7_;
  aoi21  g0(.a(x4), .b(x5), .c(x1), .O(new_n6_));
  aoi21  g1(.a(x0), .b(new_n6_), .c(x2), .O(new_n7_));
  oai21  g2(.a(x3), .b(new_n6_), .c(new_n7_), .O(z0));
endmodule
