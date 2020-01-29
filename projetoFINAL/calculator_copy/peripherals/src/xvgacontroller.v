`include "xdefs.vh"
`timescale 1ns / 1ps

module xvgacontroller (
          input   clk,
          input   rst,
          input   vsel,
          input   addr,
          input   [5:0]data_in,
          output  hs,
          output  vs,
          output [7:0]rgb
          );

	reg terminalcounter;
	reg [9:0]hcounter;
	reg [9:0]vcounter;
  reg rgbreg;
  reg hsreg;
  reg vsreg;
  wire enable;
  wire [4:0]addrinmem;
  wire [79:0]pixeldata;
  wire [4:0]addroutmem;
  wire [79:0]pixeloutput;

  xvideoencoder ve(
    .clk(clk),
    .rst(rst),
    .vsel(vsel),
    .addr2(addr),
    .data_in(data_in),
    .enable(enable),
    .addr(addrinmem),
    .data_out(pixeldata)
    );

  xvideomemory vm(
    .clk(clk),
    .enable(enable),
    .addr_in(addrinmem),
    .data_in(pixeldata),
    .addr_out(addroutmem),
    .data_out(pixeloutput)
    );

	always@(posedge clk)
	begin
    if(rst==1)
    begin
      hcounter<=10'd0;
      terminalcounter<=1'd0;
    end
    else
    begin
      if(hcounter==799)
      begin
        hsreg<=1'b1;
        hcounter<=10'd0;
        terminalcounter<=1'b1;
      end
      else
      begin
        hcounter<=hcounter + 10'd1;
        terminalcounter<=1'b0;
        if(hcounter<=94)
          hsreg<=1'b1;
        else
          hsreg<=1'b0;
      end
    end
	end

	always@(posedge clk)
	begin
    if(rst==1)
    begin
      vcounter<=10'd0;
    end
		else if(terminalcounter==1)
    begin
      if(vcounter==524)
      begin
        vcounter<=10'd0;
        vsreg<=1'b1;
      end
      else
      begin
        vcounter<=vcounter + 10'd1;
        if(vcounter<=0)
          vsreg<=1'b1;
        else
          vsreg<=1'b0;
      end
    end
    else
      vcounter<=vcounter;
	end

  always@(posedge clk)
  begin
    if(rst==1)
      rgbreg<=1'b0;
    else
    begin
      if(hcounter>=143 && hcounter<=430 && vcounter>=36 && vcounter<=45)
        rgbreg<=pixeloutput[79-(hcounter-143)%8-(vcounter-36)*8];
      else
        rgbreg<=1'b0;
    end
  end

  assign hs = hsreg;
  assign vs = vsreg;
  assign rgb = {8{rgbreg}};
  assign addroutmem = (hcounter>=143 && hcounter<=430 && vcounter>=36 && vcounter<=45) ? ((hcounter[8:0]-143)>>3) : 5'd0;


  //ecra inteiro assign rgb = (hcounter>=144 && hcounter<=783 && vcounter>=35 && vcounter<=514) ? 8'b11111111 : 8'd0;
endmodule
