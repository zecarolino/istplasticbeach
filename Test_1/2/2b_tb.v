`timescale 1ns / 1ps

module 2b_tb;
   
	reg clk;
	reg [3:0] a;
	reg [3:0] b;
	wire [7:0] c;
   
   // Instantiate the Unit Under Test (UUT)
   test_ex1 uut(
		.a(a),
		.b(b),
		.c(c),
		.clk(clk)
	     );
   
   initial begin
	$dumpfile("teste.vcd");
	$dumpvars();        

	// Initialize Inputs
	clk = 1;
	a = 0;
	b = 0;

	#25
	a = 4'b1000;
	b = 4'b0001;
	#50
	
	$finish;

   end // initial begin

	always #10 clk = ~clk;

endmodule

