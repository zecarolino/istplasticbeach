module average_tb ();
 

   reg clk, rst;
   reg x_load;
   reg [3:0] x;
   wire y;

   average avg(
		.x_load(x_load),
		.clk(clk),
		.rst(rst),
		.x(x),
		.y(y),
		);


   initial begin

      $dumpfile("dump.vcd");
      $dumpvars;

      rst = 1;
      clk = 1;

      x = 4'b0101;

      @(posedge clk) rst=0;


      @(posedge clk) x = 4'b0111;
      @(posedge clk) x = 4'b0100;
      @(posedge clk) x = 4'b1000;
      @(posedge clk) x = 4'b1111;

      @(posedge clk) $finish;
   end

   always #10 clk = ~clk;

endmodule

