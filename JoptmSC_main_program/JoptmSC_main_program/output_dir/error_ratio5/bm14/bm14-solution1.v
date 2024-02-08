module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_, new_n5_;
  oai21  g0(.a(x0), .b(x1), .c(x3), .O(new_n4_));
  oai21  g1(.a(x2), .b(x3), .c(new_n4_), .O(new_n5_));
  inv1  g2(.a(new_n5_), .O(z0));
endmodule
