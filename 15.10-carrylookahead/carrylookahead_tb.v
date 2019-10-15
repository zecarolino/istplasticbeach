`timescale 1ns / 1ps

module carrylookahead_tb;
   
	reg [3:0] a;
	reg [3:0] b;
	reg cin;
	wire carryout;
	wire [3:0] s;
   
   // Instantiate the Unit Under Test (UUT)
   top uut(
		.a(a),
		.b(b),
		.cin(cin),
		.carryout(carryout),	
		.s(s)
	     );
   
   initial begin
	$dumpfile("carrylookahead.vcd");
	$dumpvars();        

	// Initialize Inputs
	a = 0;
	b = 0;
	cin=0; 

	#25
	a = 4'b0001;
	b = 4'b1110;
	#25
	cin = 1;
	#25
	a = 4'b0001;
	b = 4'b0001;
	#25
	cin = 0;
	a = 4'b0111;
	b = 4'b0111;
	#25
	
	$finish;

   end // initial begin

endmodule

