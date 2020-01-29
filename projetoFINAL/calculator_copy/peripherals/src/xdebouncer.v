`include "xdefs.vh"
`timescale 1ns / 1ps

module xdebouncer (
                        input                   rst,
                        input                   clk,
                        output                  flag
                        );
    reg flag_reg;
    reg [`DATA_W-1:0] Q;
    assign flag = flag_reg;

    always @ (posedge clk) begin
        if (rst == 1'b1) 
            Q <= `DATA_W'hFFFFF;
        else if (Q != `DATA_W'd0)
            Q <= Q - 1;
        else 
            Q <= Q;
    end

    always @ (Q) begin
        if (Q == `DATA_W'd0)
            flag_reg = 1'b1;
        else
            flag_reg = 1'b0;
    end

endmodule
