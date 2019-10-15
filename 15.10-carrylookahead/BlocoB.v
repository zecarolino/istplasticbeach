`timescale 1ns / 1ps
module blocob

	(
	        input g0,
		input p0,
		input g1,
		input p1,
		input cin,
		output g10,
                output p10,
		output cout
	);
	
	assign g10 = g1 | p1 & g0;
	assign p10 = p1 & p0;
	assign cout = g0 | p0 & cin;

endmodule
