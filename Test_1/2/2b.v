`timescale 1ns / 1ps

module test_ex1 (
                  input clk,
                  input [3:0] a,
                  input [3:0] b,
                  output reg [7:0] c
                  );

   reg [7:0]                  y0, y1, y2;
   reg [7:0] negativea;

   always @(posedge clk) begin 
        y0 <= b[0]? a:0;
        y1 <= y0 + ((b[1]? a : 0)<<1);
        y2 <= y1 + ((b[2]? a : 0)<<2);
	negativea<={{{{{{{~a[3],~a[3]},~a[3]},~a[3]},~a[3]},~a[2]},~a[1]},~a[0]}+1;
        c  <= y2 + (b[3]? negativea : 8'd0);
   end

endmodule

