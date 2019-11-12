`timescale 1ns / 1ps

module ripplecarryadder

	(
	        input [3:0]a,
		input [3:0]b,
		input cin,
		output cout,
                output [3:0]s
	);

	wire [4:0] carry;
	assign carry[0]=cin;

	assign cout=carry[4];

	genvar i;

	generate for (i=0;i<4;i=i+1)
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
