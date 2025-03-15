
`timescale 1us/1ns

module tb_gates( );
	
	// Declare nets and variables
    reg a, b, c, d;
    wire o1, o2, o3, o4, o5, o6, o7, o8, o9, o10;
	
    // Instantiate the DUT
    built_in_gates GATES1(
        .a(a),   .b(b),   .c(c),   .d(d),
        .o1(o1), .o2(o2), .o3(o3), .o4(o4), .o5(o5), 
        .o6(o6), .o7(o7), .o8(o8), .o9(o9), .o10(o10)
    );
  
	// Generate stimulus
	initial begin
        $dumpfile("dump.vcd");
        $dumpvars(0,logical);
        #0.5; a = 1; b = 0; c = 1; d = 0;
        #1; a = 0; b = 1; c = 0; d = 1;
        #2; a = 0; b = 0; c = 1; d = 0;
        #1; a = 1; b = 1; c = 1; d = 1;
        #1; a = 0; b = 0; c = 0; d = 0;
	    #5;
	end

endmodule





