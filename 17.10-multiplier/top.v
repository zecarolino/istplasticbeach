`timescale 1ns / 1ps

module top 

	(
		input [1:0] a,
		input [1:0] b,
		output [3:0] s
	);

	wire [1:0] ab0;
	wire [1:0] ab1;
	wire carry;

	assign ab0[0] = a[0] & b[0];
	assign ab0[1] = a[1] & b[0];
	assign ab1[0] = a[0] & b[1];
	assign ab1[1] = a[1] & b[1];
	assign s[0] = ab0[0];

	halfadder ha1
	(
		.a(ab0[1]),
		.b(ab1[0]),
		.cout(carry),
                .s(s[1])
	);

	halfadder ha2
	(
		.a(ab1[1]),
		.b(carry),
		.cout(s[3]),
                .s(s[2])
	);
	
endmodule
