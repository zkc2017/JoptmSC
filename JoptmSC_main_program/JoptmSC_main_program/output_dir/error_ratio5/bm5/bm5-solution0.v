module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_;
  oai21  g0(.a(x1), .b(x3), .c(x0), .O(new_n4_));
  inv1  g1(.a(new_n4_), .O(z0));
endmodule
