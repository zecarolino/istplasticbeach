`timescale 1ns / 1ps

module top 

	(
		input [3:0] a,
		input [3:0] b,
		input cin,
		output carryout,
		output [3:0] s
	);

	wire [4:0] carry;
	assign carry[0]=cin;
	assign carryout=carry[4];
	
	wire [3:0] g;
	wire [3:0] p;
	wire [1:0] gxx;
	wire [1:0] pxx;

	genvar i;

	generate for (i=0;i<4;i=i+1)
		begin
		blocoa a    
			(
			.a(a[i]),
			.b(b[i]),
			.cin(carry[i]),
			.g(g[i]),
			.p(p[i]),
			.s(s[i])
			);
		end
	endgenerate

	generate for (i=0;i<2;i=i+1)
		begin
		blocob b    
			(
			.g0(g[2*i]),
			.p0(p[2*i]),
			.g1(g[2*i+1]),
			.p1(p[2*i+1]),
			.cin(carry[2*i]),
			.g10(gxx[i]),
			.p10(pxx[i]),
			.cout(carry[2*i+1])
			);
		end
	endgenerate

	blococ c
		(
		.g10(gxx[0]),
		.p10(pxx[0]),
		.g32(gxx[1]),
		.p32(pxx[1]),
		.cin(carry[0]),
		.cmid(carry[2]),
		.cout(carry[4])
		);

endmodule
