`include "xdefs.vh"
`timescale 1ns / 1ps

module xpixelrom (
          input   [4:0] xtoconvert,
          output reg [79:0]data_out
          );

  always @ (xtoconvert)
  begin
    case (xtoconvert)
      5'b00000 : data_out<=79'h7E7E6666666666667E7E; //0
      5'b00001 : data_out<=79'h78781818181818187E7E; //1
      5'b00010 : data_out<=79'h7E7E06067E7E60607E7E; //2
      5'b00011 : data_out<=79'h7E7E06061E1E06067E7E; //3
      5'b00100 : data_out<=79'h666666667E7E06060606; //4
      5'b00101 : data_out<=79'h7E7E60607E7E06067E7E; //5
      5'b00110 : data_out<=79'h7E7E60607E7E66667E7E; //6
      5'b00111 : data_out<=79'h7E7E0606060606060606; //7
      5'b01000 : data_out<=79'h7E7E66667E7E66667E7E; //8
      5'b01001 : data_out<=79'h7E7E66667E7E06067E7E; //9
      5'b10000 : data_out<=79'h000018187E7E18180000; //adicao
      5'b10001 : data_out<=79'h000000003C3C00000000; //subtracao
      5'b10010 : data_out<=79'h00004224181824420000; //multiplicacao
      5'b10011 : data_out<=79'h00040408081010202000; //divisaoo
      5'b10100 : data_out<=79'h002454280810142A2400; //resto
      5'b10101 : data_out<=79'h00001818242442420000; //potencias
      5'b10110 : data_out<=79'h00000E48485050200000; //raiz quadrada
      5'b10111 : data_out<=79'h18181818181818001818; //fatorial
      5'b11000 : data_out<=79'h00007E7E00007E7E0000; //igual
      default  : data_out<=79'h00000000000000000000; //
    endcase
  end

endmodule
