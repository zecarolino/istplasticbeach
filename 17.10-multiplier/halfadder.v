`timescale 1ns / 1ps
module halfadder

	(
	        input a,
		input b,
		output cout,
                output s
	);
	
	assign s = a ^ b;
	assign cout = a & b;

endmodule
