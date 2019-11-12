`timescale 1ns / 1ps
module multiplier

	(
	        input [3:0]a,
		input [3:0]b,
                output [7:0]c
	);

	wire sum1[3:0];
	wire sum2[3:0];
	wire sum3[3:0];
	wire carry1;
	wire carry2;
	wire carry3;

	assign c[0]=a[0]&b[0];
	assign c[1]=sum1[0];
	assign c[2]=sum2[0];
	assign c[6:3]=sum3;
	assign c[7]=carry3;
	
	
	ripplecarryadder rca1   (
			.a({{{1'b0,a[3]&b[0]},a[2]&b[0]},a[1]&b[0]}),
			.b({{{a[3]&b[1],a[2]&b[1]},a[1]&b[1]},a[0]&b[1]}),
			.cin(1'b0),
			.cout(carry1),
			.s(sum1)
			);
	ripplecarryadder rca2   (
			.a({carry1,sum1[3:1]}),
			.b({{{a[3]&b[2],a[2]&b[2]},a[1]&b[2]},a[0]&b[2]}),
			.cin(1'b0),
			.cout(carry2),
			.s(sum2)
			);
	ripplecarryadder rca3   (
			.a({carry2,sum2[3:1]}),
			.b({{{a[3]&b[3],a[2]&b[3]},a[1]&b[3]},a[0]&b[3]}),
			.cin(1'b0),
			.cout(carry3),
			.s(sum3)
			);

endmodule
