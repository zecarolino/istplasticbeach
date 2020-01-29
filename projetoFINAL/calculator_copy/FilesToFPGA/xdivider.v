`include "xdefs.vh"
`timescale 1ns / 1ps

module xdivider (
    input          clk,
    input          rst,
    input          [2:0]addr,
    input          dividersel,
    input          [31:0]data,
    output        [31:0]dataout
);

reg [5:0] counter;
reg [31:0] divisor;
reg [63:0] dividendo;
reg xstart;
reg done;



reg 	     quociente;
reg [31:0] resultado;


assign dataout = (addr==3'b010) ? dividendo[63:32]: ((addr==3'b011) ? dividendo[31:0]:((addr==3'b101) ? {{31{1'b0}},done}:{32{1'b0}}));


always @(posedge clk) begin
    if (rst)
        done <= 1'b0;
    else if (counter == 32)
        done <= 1'b1;
    else
        done <= 1'b0;
end

always@(posedge clk) begin
    if(rst)
        counter <= 6'd32;
    else if (xstart)
        counter <= 6'd0;
    else if (counter != 6'd32)
        counter <= counter + 1'b1;
end

always @(posedge clk) begin
    if (rst)
        xstart <= 1'b0;
    else if (addr == 4 && dividersel == 1)
        xstart <= data[0];
end

always@(posedge clk)
begin
    if(rst) begin
        dividendo <= 64'd0;
        divisor<=32'd0;
    end
    else if(dividersel==1 && addr != 3'b101) begin
        if(addr == 0 )
            dividendo<={{32{1'b0}},data};
        else if (addr == 1)
            divisor<=data;
    end
    else if (counter != 32)
        dividendo <= {{resultado [31:0],dividendo[30:0]},quociente};
end

always @* begin
    if (divisor<=dividendo[62:31]) begin
        quociente <= 1'd1;
        resultado <= dividendo[62:31] - divisor;
    end
    else begin
        quociente <= 1'd0;
        resultado <= dividendo[62:31];
    end
end
endmodule
