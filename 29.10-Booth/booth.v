`timescale 1ns / 1ps

module booth (
                     input         clk,
                     input         rst,

                     input [31:0]   M,
                     input [31:0]   m,
                     output [63:0] result,
		                 output reg done
                     );

	reg [64:0]		prodmultreg;
	reg			pc;
	reg [5:0]			counter;

	assign result = prodmultreg [64:1];

	always@(posedge clk)
	if(rst) begin
		prodmultreg <= 65'b0;
		pc<=0;
		counter<=0;
		done<=0;
    end
	else begin
		case (pc)
			0 : begin
        prodmultreg[32:1] <= m;
      end
			1 : begin
        if(done==0) begin
				case (prodmultreg[1:0])
					2'b01: begin
						prodmultreg <= $signed ({prodmultreg[64:33] + M,prodmultreg[32:0]})>>>1;
					end
					2'b10: begin
						prodmultreg <= $signed ({prodmultreg[64:33] - M,prodmultreg[32:0]})>>>1;
					end
					default: begin
						prodmultreg[63:0] <= prodmultreg[64:1];
            prodmultreg[64] <= prodmultreg[64];
					end
				endcase
        end
      end
      endcase
    if (counter == 0) begin
      pc <= pc + 1'b1;
      counter<=counter+1;
    end
    else if (counter != 6'd32) begin
			pc<=pc;
      counter<=counter+1;
    end
    else if (counter == 32) begin
			pc<=pc;
			done<=1;
			counter<=counter;
		end
	end
endmodule

module booth_tb ();

   reg clk;
   reg rst;
   reg [31:0] M;
   reg [31:0] m;
   wire [63:0] result;
   wire        done;

   booth mult0 (
                       .clk(clk),
                       .rst(rst),

                       .M(M),
                       .m(m),
                       .result(result),
                       .done(done)
                     );

   initial begin

      $dumpfile("booth.vcd");
      $dumpvars;

      rst = 1;
      clk = 1;

      M= 32'h7;
      m= 32'h8;

      @(posedge clk) #1 rst=0;

      @(posedge done) $display("%d", result);

      @(posedge clk) $finish;
   end

   always #10 clk = ~clk;

endmodule
