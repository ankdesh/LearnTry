
`timescale 1us/1ns

module adders_tree_behavioral(
   input [3:0] a,
   input [3:0] b,
   input [7:0] c,
   input [7:0] d,
   output [4:0] sum1,
   output [8:0] sum2,
   output [9:0] sum3
);
  
  // The order of the assignments in NOT important
  assign sum1 = a + b;
  assign sum3 = sum1 + sum2;
  assign sum2 = c + d;
  
endmodule
