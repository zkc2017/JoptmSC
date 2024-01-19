`timescale 1 ns/ 1 ps
module circuit_tst();
  reg clk;
  reg rst_n;
  reg[7:0] input_s;
  reg[7:0] input_b;
  wire[7:0] output_s;
  wire output_circuit;

  circuit cir(
              .clk(clk),
              .rst_n(rst_n),
              .input_s(input_s),
              .input_b(input_b),
              .output_s(output_s),
              .output_circuit(output_circuit)
  );
  initial
  begin
        input_s=1;
        input_b=0;
        rst_n=1'b0;
        clk=1'b1;
        $dumpfile("circuit.vcd");
        $dumpvars;
  #10000000; $finish;
  end
  always
  begin
  #20 input_s = output_s;
  end
  always #5100 input_b = input_b+1;
  always #10 clk = ~clk;
  always #10000000 rst_n = ~rst_n;
endmodule
