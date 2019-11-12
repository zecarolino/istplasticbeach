module average (
                  input x_load,
                  input [3:0] x,
		  input rst,
		  input clk,
                  output reg [5:0] y 
                  );
 
   reg [3:0]	x1,x2,x3,x4;
   reg [5:0]                  x12,x34;

   always @(posedge clk) begin 
	if (rst)
	begin
		y<=6'd0;
		x12<=6'd0;
		x34<=6'd0;
		x1<=4'd0;
		x2<=4'd0;
		x3<=4'd0;
		x4<=4'd0;
	end	
   end
	
   always @(posedge clk) begin 
	if (x_load)
	begin
	x4<=x3;
	x3<=x2;
	x2<=x1;
	x1<=x;
	x12<=x1+x2;
	x34<=x3+x4;
	y<=x12+x34;
	end
   end

	//nao e preciso dividir a soma por 4 porque o valor da soma ja sai representando a media se se considerar que y é 4Q2
endmodule

