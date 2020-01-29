`include "xdefs.vh"
`timescale 1ns / 1ps
 
module xhex2disp (
                        input       [3:0]number,
                        output      [6:0]segments
                        );   
	reg [6:0]data_out;
	assign segments = data_out;

	always @ (number) begin
        case (number)
            4'b0000 : data_out = 7'b1000000;
            4'b0001 : data_out = 7'b1111001;
            4'b0010 : data_out = 7'b0100100;
            4'b0011 : data_out = 7'b0110000;
            4'b0100 : data_out = 7'b0011001;
            4'b0101 : data_out = 7'b0010010;
            4'b0110 : data_out = 7'b0000010;
            4'b0111 : data_out = 7'b1111000;
            4'b1000 : data_out = 7'b0000000;
            4'b1001 : data_out = 7'b0010000;
            4'b1010 : data_out = 7'b0001000;
            4'b1011 : data_out = 7'b0000011;
            4'b1100 : data_out = 7'b1000110;
            4'b1101 : data_out = 7'b0100001;
            4'b1110 : data_out = 7'b0000110;
            4'b1111 : data_out = 7'b0001110;
            default : data_out = 7'b1000000;
        endcase
    end
endmodule
