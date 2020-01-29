`include "xdefs.vh"
`timescale 1ns / 1ps

module xvideomemory (
          input   clk,
          input   enable,
          input   [4:0]addr_in,
          input   [79:0]data_in,
          input   [4:0]addr_out,
          output   [79:0]data_out
          );

        reg [79:0] memory [0:26];

        initial
      	begin
      	$readmemh ("./vidmem.hex",memory,0,26);
      	end
       /* 
        always @ (posedge clk)
        begin
            data_out<=memory[addr_out];
        end
        */

        assign data_out=memory[addr_out];

        always @ (posedge clk)
        begin
          if(enable)
          begin
            memory[addr_in]<=data_in;
          end
        end
endmodule
