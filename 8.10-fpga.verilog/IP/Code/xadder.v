`timescale 1ns / 1ps
module xadder 
	#(parameter SIZE=32)

	(
	              input [SIZE-1:0] input1,
		      input [SIZE-1:0] input2,
                      output [SIZE-1:0] soma
	);
	
	assign soma = input1 + input2;

endmodule
