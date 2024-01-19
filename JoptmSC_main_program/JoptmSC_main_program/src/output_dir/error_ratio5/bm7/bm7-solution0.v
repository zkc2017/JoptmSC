module \solution-0 (
  x0, x1, x2, x3,
  z0 );
  input x0, x1, x2, x3;
  output z0;
  wire new_n4_;
  inv1  g0(.a(x0), .O(new_n4_));
  nor2  g1(.a(x1), .b(new_n4_), .O(z0));
endmodule
