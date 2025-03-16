`timescale 1us/1ns

module piso (
	// Testbench variables
    input sdi,
	input [3:0] d,
	input preload,
	input clk,
	input reset_n,
	output sdo
);

    reg [3:0] piso;
    wire [3:0] data_src;

    assign data_src = preload ? d : {piso[2:0],sdi};

	always @(posedge clk or negedge reset_n) begin
	    if (!reset_n)
		    piso <= 4'b0;
	    else
		    piso[3:0] <= data_src;
	end

    assign sdo = piso[3];

endmodule