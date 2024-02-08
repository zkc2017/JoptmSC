module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_;
  nand3  g0(.a(x1), .b(x2), .c(x3), .O(new_n4_));
  xnor2  g1(.a(x0), .b(new_n4_), .O(z0));
endmodule
