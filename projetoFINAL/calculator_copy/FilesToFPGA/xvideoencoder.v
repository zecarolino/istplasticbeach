`include "xdefs.vh"
`timescale 1ns / 1ps

module xvideoencoder (
    input   clk,
    input   rst,
    input   vsel,
    input   addr2,
    input   [4:0]data_in,
    output  enable,
    output  [4:0]addr,
    output  [79:0]data_out
);

reg [4:0]xaddr;
reg xenable;
reg [4:0]number;

assign enable=xenable;
assign addr=xaddr;

xpixelrom pr(
    .xtoconvert(number),
    .data_out(data_out)
);

always @ (posedge clk)
begin
    if (rst)
    begin
        xaddr<=5'd0;
        number <= 5'd0;
        xenable<=1'd0;
    end
    else if (vsel)
    begin
        if(addr2==0) begin
            xenable<=1'b0;
            xaddr<=data_in[4:0];
        end
        else
        begin
            number<=data_in[4:0];
            xenable<=1'b1;
        end
    end
    else
        xenable<=1'b0;
end //always end

endmodule
