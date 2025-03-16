`timescale 1us/1ns

module tb_shift_reg_piso();
	
	// Testbench variables
    reg sdi;
	reg [3:0] d;
	reg preload;
	reg clk = 0;
	reg reset_n;
	wire sdo;
	reg [1:0] delay;
    integer i;
	
	// Instantiate the DUT
    piso PISO0(
	    .clk(clk),
	    .reset_n(reset_n),
		.sdi(sdi),
        .preload(preload), 
        .d(d),
	    .sdo(sdo)		
    );
	
	// Create the clock signal
	always begin
	    #0.5 clk = ~clk;
	end
	
    // Create stimulus	  
    initial begin
        $dumpfile("dump.vcd");
        $dumpvars();
	    #1; // apply reset to the circuit
        reset_n = 0; sdi = 0; preload = 0; d = 0;		
		#1.3; // release the reset
		reset_n = 1;
		
		// Set sdi for 1 clock, 
		@(posedge clk); d = 4'b0101; preload = 1; @(posedge clk); preload = 0;
        
		// Wait for the bits to shift
        repeat (5) @(posedge clk); 
	end
	
    // This will stop the simulator when the time expires
    initial begin
        #40 $finish;
    end  
endmodule