module circuit(clk,rst_n,input_s,input_b,output_s,output_circuit,in_x_1,out_x_1);
  input clk;
  input rst_n;
  input[7:0] input_s;
  input[7:0] input_b;
  input in_x_1;
  output[7:0] output_s;
  output output_circuit;
  output out_x_1;

  reg[7:0] output_temp_s;
  reg out_temp_x_1;
  wire x0;
  wire x1;
  wire x2;
  wire x3;
  wire x4;
  wire x5;
  wire[7:0] comparator_binary_numer;
  wire x_temp_0;
  wire x_temp_1;
  assign output_s[7:0] = output_temp_s[7:0];
  assign output_circuit = x4;
  assign x_temp_1 = in_x_1;
  assign out_x_1 = out_temp_x_1;

  always@(posedge clk)
  begin
    if(!rst_n)
      begin
        output_temp_s[0]<=input_s[1];
        output_temp_s[1]<=input_s[2];
        output_temp_s[2]<=input_s[3];
        output_temp_s[3]<=input_s[4];
        output_temp_s[4]<=input_s[5];
        output_temp_s[5]<=input_s[6];
        output_temp_s[6]<=input_s[7];
        output_temp_s[7]<=((input_s[6]^input_s[5])^input_s[4])^input_s[0];
      end
    else
      begin
        output_temp_s<=0;
      end
  end
  assign comparator_binary_numer[0] = input_s[0];
  assign comparator_binary_numer[1] = ~input_s[1];
  assign comparator_binary_numer[2] = input_s[2];
  assign comparator_binary_numer[3] = input_s[3];
  assign comparator_binary_numer[4] = input_s[4];
  assign comparator_binary_numer[5] = input_s[5];
  assign comparator_binary_numer[6] = input_s[6];
  assign comparator_binary_numer[7] = input_s[7];
  assign x_temp_0 = (comparator_binary_numer < input_b) ? 1 : 0;

  always@(posedge clk)
  begin
    if(!rst_n)
      begin
       out_temp_x_1<=x_temp_0;
      end
    else
      begin
       out_temp_x_1<=0;
      end
  end
  assign x0=x_temp_0;
  assign x1=x_temp_1;
  assign x2=input_s[7];
  assign x3=input_s[6];

  assign x5=~(((x0)|(x3))&x2);
  assign x4=~(x1&x5);
endmodule
