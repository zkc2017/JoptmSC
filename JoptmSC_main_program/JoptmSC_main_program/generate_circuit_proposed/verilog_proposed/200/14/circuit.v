module circuit(clk,rst_n,input_s,input_b,output_s,output_circuit,in_x_1,in_x_2,out_x_1,out_x_2);
  input clk;
  input rst_n;
  input[7:0] input_s;
  input[7:0] input_b;
  input in_x_1;
  input in_x_2;
  output[7:0] output_s;
  output output_circuit;
  output out_x_1;
  output out_x_2;

  reg[7:0] output_temp_s;
  reg out_temp_x_1;
  reg out_temp_x_2;
  wire x0;
  wire x1;
  wire x2;
  wire x3;
  wire x4;
  wire x5;
  wire x6;
  wire x7;
  wire[7:0] comparator_binary_numer;
  wire x_temp_0;
  wire x_temp_1;
  wire x_temp_2;
  assign output_s[7:0] = output_temp_s[7:0];
  assign output_circuit = x5;
  assign x_temp_1 = in_x_1;
  assign x_temp_2 = in_x_2;
  assign out_x_1 = out_temp_x_1;
  assign out_x_2 = out_temp_x_2;

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
  assign comparator_binary_numer[0] = ~input_s[5];
  assign comparator_binary_numer[1] = input_s[7];
  assign comparator_binary_numer[2] = input_s[0];
  assign comparator_binary_numer[3] = input_s[6];
  assign comparator_binary_numer[4] = ~input_s[4];
  assign comparator_binary_numer[5] = ~input_s[3];
  assign comparator_binary_numer[6] = ~input_s[2];
  assign comparator_binary_numer[7] = ~input_s[1];
  assign x_temp_0 = (comparator_binary_numer < input_b) ? 1 : 0;

  always@(posedge clk)
  begin
    if(!rst_n)
      begin
       out_temp_x_1<=x_temp_0;
       out_temp_x_2<=in_x_1;
      end
    else
      begin
       out_temp_x_1<=0;
       out_temp_x_2<=0;
      end
  end
  assign x0=x_temp_0;
  assign x1=x_temp_1;
  assign x2=x_temp_2;
  assign x3=input_s[5];
  assign x4=input_s[7];

  assign x6=~(x3&x4);
  assign x7=((x0)&(~x1))|((~x0)&(x1));
  assign x5=~(((x2)&(x6))|x7);
endmodule
