`include "xdefs.vh"
`timescale 1ns / 1ps

module x7segments_controller (
                        input                   rst,
                        input                   clk,
                        input                   seg7_sel,
                        input       			[3:0]data_to_wr,
                        input               [1:0]addr,
                        output              [7:0]segments,
                        output              [3:0]enable
                        );
    
    wire [6:0]encoder_out;
    wire [6:0]reg_dig0_out;
    wire [6:0]reg_dig1_out;
    wire [6:0]reg_dig2_out;
    wire [6:0]reg_dig3_out;

    reg [1:0]dot;

    wire enbale_reg_dig0;
    wire enbale_reg_dig1;
    wire enbale_reg_dig2;
    wire enbale_reg_dig3;

    reg [7:0] data_out;
    reg [15:0] contador;

    assign segments = data_out;

    reg [3:0] reg_enable;

    assign enable = reg_enable;

    assign enbale_reg_dig0 = seg7_sel & ( ~addr[0] & ~addr[1] );
    assign enbale_reg_dig1 = seg7_sel & ( addr[0] & ~addr[1] );
    assign enbale_reg_dig2 = seg7_sel & ( ~addr[0] & addr[1] );
    assign enbale_reg_dig3 = seg7_sel & ( addr[0] & addr[1] );

    xhex2disp encoder (
        .number(data_to_wr),
        .segments(encoder_out)
    );

    xregister #(.N(7),.INIT(7'b1000000)) reg_digit_0 (
        .rst(rst),
        .clk(clk),
        .enable(enbale_reg_dig0),
        .D(encoder_out),
        .Q(reg_dig0_out)
        ); 

    xregister #(.N(7),.INIT(7'b1000000)) reg_digit_1 (
        .rst(rst),
        .clk(clk),
        .enable(enbale_reg_dig1),
        .D(encoder_out),
        .Q(reg_dig1_out)
        ); 

    xregister #(.N(7),.INIT(7'b1000000)) reg_digit_2 (
        .rst(rst),
        .clk(clk),
        .enable(enbale_reg_dig2),
        .D(encoder_out),
        .Q(reg_dig2_out)
        ); 

    xregister #(.N(7),.INIT(7'b1000000)) reg_digit_3 (
        .rst(rst),
        .clk(clk),
        .enable(enbale_reg_dig3),
        .D(encoder_out),
        .Q(reg_dig3_out)
        ); 
    
	 always @ (posedge clk) begin
        if (rst == 1'b1) 
            contador <= 15'd0;
        else if (contador >= 16'd50000)
            contador <= 15'd0;
		else
			contador <= contador + 16'b1;
    end
	  
    always @ (posedge clk) begin
        if (rst == 1'b1) 
            reg_enable <= 4'b1110;
        else if (contador >= 16'd50000)
            reg_enable <= {reg_enable[2:0],reg_enable[3]};
		else
			reg_enable <= reg_enable;
    end

    always @ (posedge clk) begin
        if (rst == 1'b1)
            dot <= 2'b00;
        else if (enbale_reg_dig0)
            dot <= 2'b00;
        else if (enbale_reg_dig1)
            dot <= 2'b01;
        else if (enbale_reg_dig2)
            dot <= 2'b10;
        else if (enbale_reg_dig3)
            dot <= 2'b11;
        else
            dot <= dot;
    end

    always @ (dot or reg_dig0_out or reg_dig1_out or reg_dig2_out or reg_dig3_out or reg_enable) begin
        case (reg_enable)
            4'b1110 : data_out = (dot == 2'b00) ? {1'b0,reg_dig0_out}:{1'b1,reg_dig0_out};
            4'b1101 : data_out = (dot == 2'b01) ? {1'b0,reg_dig1_out}:{1'b1,reg_dig1_out};
            4'b1011 : data_out = (dot == 2'b10) ? {1'b0,reg_dig2_out}:{1'b1,reg_dig2_out};
            4'b0111 : data_out = (dot == 2'b11) ? {1'b0,reg_dig3_out}:{1'b1,reg_dig3_out};
            default : data_out = 8'b01000000;
        endcase
    end

endmodule
