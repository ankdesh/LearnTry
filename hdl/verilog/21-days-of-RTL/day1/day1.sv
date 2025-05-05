// A simple mux
`timescale 1ns/1ps // Define simulation time units

module day1 (
  input   logic [7:0]    a_i,
  input   logic [7:0]    b_i,
  input   logic          sel_i,
  output  logic [7:0]    y_o
);
//  logic [7:0] y_o_reg;
always @(sel_i, a_i, b_i) begin
    if (sel_i) 
      y_o <= a_i;
    else
      y_o <= b_i;
end
endmodule