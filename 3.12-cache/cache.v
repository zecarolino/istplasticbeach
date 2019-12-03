`timescale 1ns / 1ps
//se nao der hit nao chego a escrever....
module cache
	(
	  input clk,
		input rst,
		input [34:0]addr, //34:11 tag , 10:3 index , 2:0 offset
		input valid,
		input write,
		input [31:0]data_in,
		output reg [31:0]data_out,
		output hitmiss
	);

	reg [23:0] tagmem [255:0];
	reg [31:0] word1 [255:0];
	reg [31:0] word2 [255:0];
	reg [31:0] word3 [255:0];
	reg [31:0] word4 [255:0];
	reg [31:0] word5 [255:0];
	reg [31:0] word6 [255:0];
	reg [31:0] word7 [255:0];
	reg [31:0] word8 [255:0];

	reg [23:0]tag_rd;


	always @(posedge clk)
	begin
		if (rst)
		begin
			tagmem[0]<=24'hFFFFFF;
			word1[0]<=32'd0;
			tagmem[1]<=24'h111111;
			word2[1]<=32'd1;
			tagmem[2]<=24'h555555;
			tagmem[3]<=24'hAAAAAA;
			tag_rd<=24'd0;
		end
		else if (valid)
		begin
			tag_rd<=tagmem[addr[10:3]];
			case (addr[2:0])
				3'b000 : data_out<=word1[addr[10:3]];
				3'b001 : data_out<=word2[addr[10:3]];
				3'b010 : data_out<=word3[addr[10:3]];
				3'b011 : data_out<=word4[addr[10:3]];
				3'b100 : data_out<=word5[addr[10:3]];
				3'b101 : data_out<=word6[addr[10:3]];
				3'b110 : data_out<=word7[addr[10:3]];
				3'b111 : data_out<=word8[addr[10:3]];
			endcase
			if(write==1 && tagmem[addr[10:3]]==addr[34:11])
			begin
				case (addr[2:0])
					3'b000 : word1[addr[10:3]]<=data_in;
					3'b001 : word2[addr[10:3]]<=data_in;
					3'b010 : word3[addr[10:3]]<=data_in;
					3'b011 : word4[addr[10:3]]<=data_in;
					3'b100 : word5[addr[10:3]]<=data_in;
					3'b101 : word6[addr[10:3]]<=data_in;
					3'b110 : word7[addr[10:3]]<=data_in;
					3'b111 : word8[addr[10:3]]<=data_in;
				endcase
			end
		end
		else
			tag_rd<=tagmem[addr[10:3]];
	end

	assign hitmiss = (addr[34-:24]==tag_rd && valid==1);

endmodule

module cache_tb ();

   reg clk, rst;
	 reg valid, write;
   reg [34:0] addr;
   wire [31:0] data_in,data_out;
   wire hitmiss;

   cache c0 (
  			.clk(clk),
      	.rst(rst),
     		.valid(valid),
      	.write(write),
		  	.addr(addr),
      	.data_in(data_in),
      	.data_out(data_out),
      	.hitmiss(hitmiss)
    		);

   initial begin

      $dumpfile("dump.vcd");
      $dumpvars;

      rst = 1;
      clk = 1;
			valid = 0;
			write = 0;
			addr=35'b11111111111111111111111100000000000;
			#20
			rst=0;
			#100
			valid=1;
			#100
			addr=35'b11111111111111111111111100000001001;
      #100
			$finish;
   end

   always #10 clk = ~clk;

endmodule
