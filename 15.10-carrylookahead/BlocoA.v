`timescale 1ns / 1ps
module blocoa

	(
	        input a,
		input b,
		input cin,
		output g,
                output p,
		output s
	);
	
	assign s = a ^ b ^ cin;
	assign g = a & b;
	assign p = a ^ b;

endmodule
