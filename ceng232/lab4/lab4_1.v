`timescale 1ns / 1ps

module ROM (
input [2:0] addr, 
output reg [7:0] dataOut);

	// write your code below
	always @ (addr) begin
		case(addr)
			3'b000  : dataOut = 8'b00000000;
			3'b001  : dataOut = 8'b01010101;
			3'b010  : dataOut = 8'b10101010;
			3'b011  : dataOut = 8'b00110011;
			3'b100  : dataOut = 8'b11001100;
			3'b101  : dataOut = 8'b00001111;
			3'b110  : dataOut = 8'b11110000;
			3'b111  : dataOut = 8'b11111111;
		endcase
	end
endmodule


module XOR_RAM (
input mode, 
input [2:0] addr, 
input [7:0] dataIn, 
input [7:0] mask, 
input CLK, 
output reg [7:0] dataOut);
	
	reg [7:0] data [7:0];
	integer i;
	
	initial begin
		dataOut <= 0;
		for(i = 0; i <= 7; i=i+1)
			data[i] <= 0;
	end
	
	// write your code below
		
	always@(data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],mode,addr) begin
		if(mode)
			dataOut <= data[addr];
	end
	
	always@(posedge CLK) begin
		if(~mode)
			data[addr] <= dataIn ^ mask;
	end
	
endmodule


module EncodedMemory (
input mode, 
input [2:0] index, 
input [7:0] number, 
input CLK, 
output [7:0] result);
	
	// DO NOT EDIT THIS MODULE
	
	wire [7:0] mask;
	
	ROM R(index, mask);
	XOR_RAM XR(mode, index, number, mask, CLK, result);

endmodule
