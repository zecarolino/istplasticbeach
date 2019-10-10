`timescale 1ns / 1ps

module fulladder_tb;
   
	reg [31:0] a;
	reg [31:0] b;
	reg cin;
	wire overflow;
	wire carryout;
	wire [31:0] s;
   
   // Instantiate the Unit Under Test (UUT)
   top #(.SIZE(32)) uut(
		.a(a),
		.b(b),
		.cin(cin),
		.overflow(overflow),
		.carryout(carryout),	
		.s(s)
	     );
   
   initial begin
	$dumpfile("fulladder.vcd");
	$dumpvars();        

	// Initialize Inputs
	a = 0;
	b = 0;
	cin=0; 

	#25
	a = 32'hFFFFFFFF;
	b = 32'h00000001;
	#25
	a = 32'hFFFFFFFF;
	b = 32'hFFFFFFFF;
	#25
	a = 32'h7FFFFFFF;
	b = 32'h00000001;
	#25
	a = -31;
	b = -31;
	cin = 1;
	#25
	
	$finish;

   end // initial begin

endmodule

