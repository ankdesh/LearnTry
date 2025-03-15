`timescale 1us/1ns

module adders3_procedural(
   input [3:0] a,
   input [3:0] b,
   input [7:0] c,
   input [7:0] d,
   output reg [4:0] sum1,
   output reg [8:0] sum2,
   output reg [9:0] sum3
);
  
    // The order of the assignments in NOT important  
    always @(a or b) begin
        sum1 = a+b;
    end
    
    always @(c or d) begin
        sum2 = c + d;
    end
    
    // Best practice control list
    // Any change in RHS propagates to LHS
    always @(*) begin
        sum3 = sum1 + sum2;
    end 
    
    /*
    always @(*) begin
        sum3 = a + b + c + d;
    end  */
  
endmodule
