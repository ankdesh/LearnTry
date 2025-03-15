`timescale 1us/1ns

module d_latch(
    input d,
	input enable,
	output q,
    output q_not
    );
	
	reg dlatch;
	
	// The D-Lach is level sensitive
	always @(enable or d) begin
	    if(enable)
		    dlatch <= d; 
	end
	
	assign q = dlatch;
	assign q_not = ~q;
	
endmodule