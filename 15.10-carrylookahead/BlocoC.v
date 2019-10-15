`timescale 1ns / 1ps
module blococ

	(
	        input g10,
		input p10,
		input g32,
		input p32,
		input cin,
		output cmid,
		output cout
	);
	
	wire g30;
	wire p30;
	
	assign g30 = g32 | p32 & g10;
	assign p30 = p32 & p10;
	assign cmid = g10 | p10 & cin;
	assign cout = g30 | p30 & cin;

endmodule
