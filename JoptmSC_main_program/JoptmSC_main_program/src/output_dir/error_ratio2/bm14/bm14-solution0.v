module \solution-0 (
  x0, x1, x2, x3, x4,
  z0 );
  input x0, x1, x2, x3, x4;
  output z0;
  wire new_n5_, new_n6_, new_n7_;
  xor2  g0(.a(x0), .b(x1), .O(new_n5_));
  nor3  g1(.a(x2), .b(x3), .c(x4), .O(new_n6_));
  or2  g2(.a(new_n5_), .b(new_n6_), .O(new_n7_));
  aoi21  g3(.a(x0), .b(x4), .c(new_n7_), .O(z0));
endmodule
