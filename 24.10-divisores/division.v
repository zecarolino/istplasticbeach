`timescale 1ns / 1ps

module division (
                     input         clk,
                     input         rst,
                     
                     input [3:0]   D, 
                     input [3:0]   d,
		     output [3:0]  q,
                     output [3:0]  r,
                     input         start,
                     output        done
                     );

   reg [3:0] counter;
   reg [3:0] divisor;
   reg [7:0] dividendo;
   reg 	     quociente;
   reg [3:0] resultado;



   assign q = dividendo [3:0];
   assign r = dividendo [7:4];

   assign done = (counter == 4'd4);

   always@(posedge clk)
     if(rst)
       counter <= 4'd4;
     else if (start)
       counter <= 4'd0;
     else if (counter != 4'd4)
       counter <= counter + 1'b1;
   
     always@(posedge clk)
	divisor <= d;

     always@(posedge clk)
	if(rst)
		dividendo <= 8'd0;
	else if (start)
		dividendo <= {4'd0,D[3:0]};
	else if (counter != 4'd4)
		dividendo <= {{resultado [3:0],dividendo[2:0]},quociente};

     always@*
	if (divisor<=dividendo[6:3]) begin
		quociente <= 1'd1;
		resultado <= dividendo[6:3] - divisor;
	end
	else begin
		quociente <= 1'd0;
		resultado <= dividendo[6:3];
	end

endmodule


module division_tb ();

   reg clk, rst;
   reg [3:0] D, d;
   wire [3:0] q,r;
   reg         start;
   wire        done;
   
   division div (
                       .clk(clk),
                       .rst(rst),
                     
                       .D(D), 
                       .d(d),
		       .q(q), 
                       .r(r),
                       .start(start),
                       .done(done)
                     );   

   initial begin

      $dumpfile("dump.vcd");
      $dumpvars;
      
      rst = 1;
      clk = 1;
      start = 0;

      D= 4'h4;
      d= 4'h4;

      @(posedge clk) #1 rst=0;

      #5 @(posedge clk) #1 start=1;
      @(posedge clk) #1 start=0;

      @(posedge done) $display("%d", q);
      
      @(posedge clk) $finish;
   end
   
   always #10 clk = ~clk;
 
endmodule
