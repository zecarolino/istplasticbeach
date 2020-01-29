`include "xdefs.vh"
`timescale 1ns / 1ps

module xmultiplier (
    input                   clk,
    input                   rst,
    input                   multsel,
    input                   [15:0]number,
    input                   [1:0]addr,
    output                  [31:0]data_out
);

reg [15:0] number1;
reg [15:0] number2;

wire [31:0] mult;

assign mult = number1*number2;


assign data_out =  (addr == 2) ? mult:32'd0;

always @ (posedge clk)
begin
    if (rst==1)
    begin
        number1<=16'd0;
        number2<=16'd0;
    end
    else
    begin
        if (multsel)
        begin
            if (addr == 0)
                number1<=number;
            else if (addr == 1 )
                number2<=number;
        end
    end
end
endmodule
