`timescale 1ns / 1ps

module xadder_tb;
   
	reg [31:0] input1;
	reg [31:0] input2;
	wire [31:0] soma;
   
   // Instantiate the Unit Under Test (UUT)
   xadder #(.SIZE(32)) uut(
	     .input1(input1),
	     .input2(input2),
	     .soma(soma)
	     );
   
   initial begin
	$dumpfile("adder.vcd");
	$dumpvars();        

	// Initialize Inputs
	input1 = 0;
	input2 = 0; 


	#25
	input1 = 32'h4456FF21;
	input2 = 32'h234522EF;
	#25
	input1 = 32'h00000001;
	input2 = 32'hFFFFFFFF;
	#25
	input1 = 32'h00000001;
	input2 = 32'h00000001;
	#25
	input1 = 32'hF;
	input2 = 32'hF;
	#25
	
	$finish;

   end // initial begin

endmodule

