`timescale 1ns / 1ps
`include "xdefs.vh"


module xtop (
	        input               clk50,
	        input               rst,
            input   [2:0]       butt,
            output  [3:0]       digit,
            output  [7:0]       segment,
            output              trap,
						output 	[7:0]				rgb,
						output 							hs,
						output 							vs

`ifndef NO_EXT
	     // external parallel interface
	     ,  output [`ADDR_W-2:0] par_addr,
	        input [`DATA_W-1:0]  par_in,
            output               par_re,
	        output [`DATA_W-1:0] par_out,
	        output               par_we
`endif
	     );

	  reg flipflopclock;
		wire clk;


    //
    // CONNECTION WIRES
    //

    // INSTRUCTION MEMORY INTERFACE
    wire [`INSTR_W-1:0] 		  instruction;
    wire [`ADDR_W-2:0]             pc;

    // DATA BUS
    wire 			  data_sel;
    wire 			  data_we;
    wire [`ADDR_W-1:0] 		  data_addr;
    wire [`DATA_W-1:0] 		  data_to_rd;
    wire [`DATA_W-1:0] 		  data_to_wr;


    // ADDRESS DECODER
    wire                    mem_sel;
    wire [`DATA_W-1:0] 		mem_data_to_rd;

    wire				    regf_sel;
    wire [`DATA_W-1:0] 		regf_data_to_rd;

    wire                    seg7_sel;
    wire                    vga_sel;

    wire                    butt_sel;
    wire [`DATA_W-1:0]      butt_data_to_rd;
    wire                    mult_sel;
    wire [`DATA_W-1:0]      mult_data_to_rd;
    wire                    div_sel;
    wire [31:0]      div_data_to_rd;

`ifdef DEBUG
    reg 				  cprt_sel;
`endif

`ifndef NO_EXT
    wire                           ext_sel;
    wire [`DATA_W-1:0]             ext_data_to_rd = par_in;

    //External interface
    assign par_addr = data_addr[`ADDR_W-2:0];
    assign par_re = ext_sel & ~data_we;
    assign par_out = data_to_wr;
    assign par_we = ext_sel & data_we;
`endif

   //
   // CONTROLLER MODULE
   //
   xctrl controller (
		    .clk(clk),
		    .rst(rst),

		    // Program memory interface
		    .pc(pc),
		    .instruction(instruction),

		    // mem data bus
		    .mem_sel(data_sel),
		    .mem_we (data_we),
		    .mem_addr(data_addr),
		    .mem_data_from(data_to_rd),
		    .mem_data_to(data_to_wr)
		    );

   // MEMORY MODULE
   xram ram (
	        .clk(clk),

	        // instruction interface
	        .pc(pc),
       	    .instruction(instruction),

	        //data interface
	        .data_sel(mem_sel),
	        .data_we(data_we),
	        .data_addr(data_addr[`ADDR_W-2 : 0]),
	        .data_in(data_to_wr),
	        .data_out(mem_data_to_rd)
	       );


   // REGISTER FILE
   xregf regf (
	       .clk(clk),
	       .sel(regf_sel),
	       .we(data_we),
	       .addr(data_addr[`REGF_ADDR_W-1:0]),
	       .data_in(data_to_wr),
	       .data_out(regf_data_to_rd)
	       );

   // INTERNAL ADDRESS DECODER

   xaddr_decoder addr_decoder (
	                        // input select and address
                            .sel(data_sel),
	                        .addr(data_addr),

                            //memory
	                        .mem_sel(mem_sel),
                            .mem_data_to_rd(mem_data_to_rd),

                            //registers
	                        .regf_sel(regf_sel),
                            .regf_data_to_rd(regf_data_to_rd),

                            .seg7_sel(seg7_sel),
                            .vga_sel(vga_sel),

                            .butt_sel(butt_sel),
                            .butt_data_to_rd(butt_data_to_rd),
                            .mult_sel(mult_sel),
                            .mult_data_to_rd(mult_data_to_rd),
                            .div_sel(div_sel),
                            .div_data_to_rd(div_data_to_rd),
`ifdef DEBUG
                            //debug char printer
	                        .cprt_sel(cprt_sel),
`endif

`ifndef NO_EXT
                            //external
                            .ext_sel(ext_sel),
                            .ext_data_to_rd(ext_data_to_rd),
`endif

                            //trap
                            .trap_sel(trap),

                            //data output
                            .data_to_rd(data_to_rd)
                            );

   //
   //
   // USER MODULES INSERTED BELOW
   //
   //

`ifdef DEBUG
   xcprint cprint (
		   .clk(clk),
		   .sel(cprt_sel & data_we),
		   .data_in(data_to_wr[7:0])
		   );
`endif

    x7segments_controller segments7 (
            .rst(rst),
            .clk(clk),
            .seg7_sel(seg7_sel),
            .data_to_wr(data_to_wr[3:0]),
            .addr(data_addr[`SEG7_ADDR_W-1:0]),
            .segments(segment),
            .enable(digit)
    );

    xbutton_controller buttons (
            .rst(rst),
            .butt_sel(butt_sel),
            .clk(clk),
            .bt(butt),
            .addr(data_addr[`BUTT_ADDR_W-1:0]),
            .data_to_rd(butt_data_to_rd)
    );
    
    xvgacontroller vgacontroller (
            .clk(clk),
            .rst(rst),
            .vsel(vga_sel),
            .addr(data_addr[0]),
            .data_in(data_to_wr[5:0]),
            .hs(hs),
            .vs(vs),
            .rgb(rgb)
    );

    xmultiplier multiplier(
            .clk(clk),
            .rst(rst),
            .multsel(mult_sel),
            .number(data_to_wr[15:0]),
            .addr(data_addr[1:0]),
            .data_out(mult_data_to_rd)
    );

    xdivider divider(
            .clk(clk),
            .rst(rst),
            .addr(data_addr[2:0]),
            .dividersel(div_sel),
            .data(data_to_wr),
            .dataout(div_data_to_rd)
);

	always @ (posedge clk50)
	begin
        if (rst == 1)
            flipflopclock<=1'b0;
        else
            flipflopclock<=~flipflopclock;
        end
/*
    BUFG bufg0 (
        .I(flipflopclock),
        .O(clk)
    );
*/
    assign clk = clk50;
endmodule
