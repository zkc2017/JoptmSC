module \solution-0 (
  x0, x1, x2, x3, x4, x5,
  z0 );
  input x0, x1, x2, x3, x4, x5;
  output z0;
  wire new_n6_, new_n7_;
  oai21  g0(.a(x2), .b(x4), .c(x3), .O(new_n6_));
  oai22  g1(.a(x0), .b(x1), .c(x2), .d(new_n6_), .O(new_n7_));
  oai21  g2(.a(x5), .b(new_n6_), .c(new_n7_), .O(z0));
endmodule
