`timescale 1ns / 1ps
module kb(
	input K,
	input B,
	input clk,
	output reg Q
	);
    
	initial begin
		Q = 0;
	end
	 
	always @ (posedge clk)
		if((K == 0) && (B == 0))
			Q <= ~Q;
		else if ((K == 0) && (B == 1))
			Q <= 0;
		else if ((K == 1) && (B == 0))
			Q <= 1;
		else
			Q <= Q;
		
		
endmodule


module ic232(
	input A0, 
	input A1, 
	input A2, 
	input clk,
	output Q0,
	output Q1,
	output Z
	);
	
	kb kb0 ( .K(~(A0 | A1) & (~A2)),
				.B(A1),
				.clk(clk),
				.Q(Q0));
	
	kb kb1 ( .K(~A2),
				.B((~A0|A1)^A2),
				.clk(clk),
				.Q(Q1));
				
	assign Z = Q0 ~^ Q1;
	
endmodule
