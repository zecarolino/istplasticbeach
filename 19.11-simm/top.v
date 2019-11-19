`timescale 1ns/1ps

module top (
  input 	   [20:0] addr,
  input 	   ras,
  input 	   cas,
  input 	   we,
  output reg [15:0] data_out
);

	reg [7:0] ras_decoder;

	always @ (*)
	begin
		ras_decoder[7:0]<=8'b11111111;
		case (addr [20:18])
			3b'000 : ras_decoder[0]<=1'b0;
			3b'001 : ras_decoder[1]<=1'b0;
			3b'010 : ras_decoder[2]<=1'b0;
			3b'011 : ras_decoder[3]<=1'b0;
			3b'100 : ras_decoder[4]<=1'b0;
			3b'101 : ras_decoder[5]<=1'b0;
			3b'110 : ras_decoder[6]<=1'b0;
			3b'111 : ras_decoder[7]<=1'b0;
			default : ras_decoder[7:0]<=8'b11111111;
		endcase
	end

	simm module0 (
		.cas({4{cas}}),
		.addr(addr[17:0]),
		.we(we),
		.ras(ras_decoder[1:0]),
		.data_out(data_out)	
		);

	simm module1 (
		.cas({4{cas}}),
		.addr(addr[17:0]),
		.we(we),
		.ras(ras_decoder[3:2]),
		.data_out(data_out)	
		);

	simm module2 (
		.cas({4{cas}}),
		.addr(addr[17:0]),
		.we(we),
		.ras(ras_decoder[5:4]),
		.data_out(data_out)	
		);

	simm module3 (
		.cas({4{cas}}),
		.addr(addr[17:0]),
		.we(we),
		.ras(ras_decoder[7:6]),
		.data_out(data_out)	
		);

endmodule
