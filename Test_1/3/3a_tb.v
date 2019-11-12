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

      @(posedge clk) begin
	end

      #5 @(posedge clk) #1 start=1;
      @(posedge clk) #1 start=0;

      @(posedge done) $display("%d", c);

      @(posedge clk) $finish;
   end

   always #10 clk = ~clk;

endmodule

