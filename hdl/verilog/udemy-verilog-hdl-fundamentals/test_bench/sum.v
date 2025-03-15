module adder_8bit (
    input [7:0] a,
    input [7:0] b,
    output [8:0] sum
    );
    
    assign sum = a + b;
    
endmodule