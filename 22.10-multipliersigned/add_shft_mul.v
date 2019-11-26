`timescale 1ns / 1ps

module add_shft_mul (
                     input         clk,
                     input         rst,

                     input signed [7:0]   a,
                     input signed [7:0]   b,
                     output reg signed [15:0] c,
                     input         start,
                     output        done
                     );

   reg [3:0]                     counter;


   assign done = (counter == 4'd8);

   always@(posedge clk)
     if(rst)
       counter <= 4'd8;
     else if (start)
       counter <= 4'd0;
     else if (counter != 4'd8)
       counter <= counter + 1'b1;


     always@(posedge clk)
     if(rst)
       c <= 16'd0;
     else if(counter != 4'd8) begin
	if (counter == 4'd7 && b[counter]==1)
		c <= {c[15],c[15:1]} - {{a[7],a[7:0]},7'b0};
	else
        	c <= {c[15],c[15:1]} + (b[counter]? {{a[7],a[7:0]},7'b0}: 16'd0); //se for dif 0 a<<7 se ==0 16'd0
     end
endmodule


module add_shft_mul_tb ();

   reg clk, rst;
   reg [7:0] a, b;
   wire [15:0] c;
   reg         start;
   wire        done;

   add_shft_mul mult0 (
                       .clk(clk),
                       .rst(rst),

                       .a(a),
                       .b(b),
                       .c(c),
                       .start(start),
                       .done(done)
                     );

   initial begin

      $dumpfile("dump.vcd");
      $dumpvars;

      rst = 1;
      clk = 1;
      start = 0;

      b= 8'h64;
      a = 8'hbf;

      @(posedge clk) #1 rst=0;

      #5 @(posedge clk) #1 start=1;
      @(posedge clk) #1 start=0;

      @(posedge done) $display("%d", c);

      @(posedge clk) $finish;
   end

   always #10 clk = ~clk;

endmodule
