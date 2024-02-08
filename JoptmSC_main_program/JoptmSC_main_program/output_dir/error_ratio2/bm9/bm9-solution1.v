module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_;
  nor2  g0(.a(x0), .b(x1), .O(new_n4_));
  oai21  g1(.a(x3), .b(new_n4_), .c(x2), .O(z0));
endmodule
