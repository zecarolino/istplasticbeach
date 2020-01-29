`include "xdefs.vh"
`timescale 1ns / 1ps

module xregister 
                #(parameter N=`DATA_W, parameter INIT={N{1'b0}})
                (
                    input                   rst,
                    input                   clk,
                    input                   enable,
                    output          [N-1:0]Q,
                    input           [N-1:0]D
                );

    reg [N-1:0]data_out;

    assign Q = data_out;
    always @ (posedge clk) begin
		  data_out <= {N{1'b0}};
        if (rst == 1'b1) 
            data_out <= INIT;
        else if (enable == 1'b1)
            data_out <= D;
        else 
            data_out <= data_out;
    end

endmodule
