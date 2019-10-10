`timescale 1ns / 1ps

module top 

	#(parameter SIZE=32)

	(
		input [SIZE-1:0] a,
		input [SIZE-1:0] b,
		input cin,
		output overflow,
		output carryout,
		output [SIZE-1:0] s
	);

	wire [SIZE:0] carry;
	assign carry[0]=cin;
	
	assign carryout=carry[SIZE];
	assign overflow=carry[SIZE] ^ carry[SIZE-1];

	genvar i;

	generate for (i=0;i<SIZE;i=i+1)
		begin
		fulladder fa    (
					.a(a[i]),
					.b(b[i]),
					.cin(carry[i]),
					.cout(carry[i+1]),
					.s(s[i])
				);
		end
	endgenerate
endmodule
