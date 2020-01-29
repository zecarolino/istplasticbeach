`include "xdefs.vh"
`timescale 1ns / 1ps

module xbutton_controller (
                        input                   rst,
                        input                   butt_sel,
                        input                   clk,
                        input               [2:0]bt,
                        input               [1:0]addr,
                        output      [`DATA_W-1:0]data_to_rd
                        );
    wire Q_bt1;
    wire Q_bt2;
    wire Q_bt3;
    reg [`DATA_W-1:0] data_out;

    wire D_bt1;
    wire D_bt2;
    wire D_bt3;

    assign data_to_rd = data_out;
    
    always @ (Q_bt1 or Q_bt2 or Q_bt3 or addr or butt_sel) begin
        if (butt_sel != 1'b1)
            data_out = `DATA_W'd0;
        else begin
            case (addr)
                2'b00 : data_out = {31'd0,Q_bt1};
                2'b01 : data_out = {31'd0,Q_bt2};
                2'b10 : data_out = {31'd0,Q_bt3};
                2'b11 : data_out = {31'd0,Q_bt3};
                default : data_out = `DATA_W'd0;
            endcase
        end
    end

    xregister #(.N(1))bt1 (
                .rst(rst),
                .clk(clk),
                .enable(1'b1),
                .D(D_bt1),
                .Q(Q_bt1)
                ); 

    xregister #(.N(1))bt2 (
                .rst(rst),
                .clk(clk),
                .enable(1'b1),
                .D(D_bt2),
                .Q(Q_bt2)
                );

    xregister #(.N(1))bt3 (
                .rst(rst),
                .clk(clk),
                .enable(1'b1),
                .D(D_bt3),
                .Q(Q_bt3)
                ); 

    xdebouncer bt1_debounce (
                .rst(~bt[0] | rst),
                .clk(clk),
                .flag(D_bt1)
                );

    xdebouncer bt2_debounce (
                .rst(~bt[1] | rst),
                .clk(clk),
                .flag(D_bt2)
                );

    xdebouncer bt3_debounce (
                .rst(~bt[2] | rst),
                .clk(clk),
                .flag(D_bt3)
                );
endmodule
