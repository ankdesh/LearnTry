// Testbench for day1 module
`timescale 1ns/1ps // Define simulation time units

module day1_tb;

  // Declare signals to connect to the DUT (Device Under Test)
  logic [7:0] a;
  logic [7:0] b;
  logic       sel;
  logic [7:0] y;

  // Instantiate the DUT
  day1 dut (
    .a_i    (a),
    .b_i    (b),
    .sel_i  (sel),
    .y_o    (y)
  );

  // Test stimulus
  initial begin
    $display("Starting Day 1 Mux Testbench...");
    $monitor("Time=%0t: a=%h, b=%h, sel=%b => y=%h", $time, a, b, sel, y);

    // Initialize inputs
    a = 8'hAA;
    b = 8'h55;
    sel = 1'b0;
    #10; // Wait for 10 time units

    // Test case 1: sel = 1
    sel = 1'b1;
    #10;

    // Test case 2: Change inputs while sel = 1
    a = 8'hF0;
    b = 8'h0F;
    #10;

    // Test case 3: sel = 0 again
    sel = 1'b0;
    #10;

    $display("Testbench finished.");
    $finish; // End the simulation
  end

endmodule