`timescale 1ns / 1ps

module fibonnacci (
                     input [3:0]   a,
                     output [5:0]   number

                     );

	reg [5:0] memrom[0:9];

	initial
	begin
	$readmemb ("program.hex",memrom,0,9);
	end

	assign number=memrom[a];

endmodule

module fibonnacci_tb ();

  parameter T=10;

   reg [3:0] a;
   wire [5:0] number;


   fibonnacci sequence (
                       .a(a),
                       .number(number)
                     );

   initial begin

      $dumpfile("fibonnacci.vcd");
      $dumpvars;

      a= 4'b0;

      #(21*T)

      $finish;
   end
   always #10
    if(a!=9)
      a = a+1;
    else
      a = 0;

endmodule
