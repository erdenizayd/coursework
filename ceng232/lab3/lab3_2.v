`timescale 1ns / 1ps
module QueueCounter(
	input [7:0] llmt,
	input [7:0] ulmt,
	input en,
	input mode, // 1:delete, 0:insert
	input clk,
	output reg [7:0] head,
	output reg [7:0] tail,
	output empty,
	output full);
	
	//you may write your code here
	reg [7:0] count;
	
	initial
	begin
		head = llmt;
		tail = llmt;
		count = 0;
	end

	assign empty = ((head == tail) && (count == 0));
	assign full = ((head == tail) && (~empty));
		


	always @ (posedge clk) begin
		if (en == 1) begin
			if (mode == 0) begin
				if(~full) begin
					if(tail == ulmt) begin
						tail = llmt;
						count = count + 1;
					end else begin
						tail = tail + 1;
						count = count + 1;
					end
				end
			end
			if (mode == 1) begin
				if(~empty) begin
					if(head == ulmt) begin
						head = llmt;
						count = count - 1;
					end else begin
						head = head + 1;
						count = count - 1;
					end
				end
			end
		end
	end
	//you may write your code here


endmodule


module Numerator(
	input clinic, 
	input mode, 
	input en, 
	input clk,
	output [7:0] ann,
	output [7:0] print);
	
	wire [7:0] a0;
	wire [7:0] a1;
	wire [7:0] p0;
	wire [7:0] p1;
	wire empty_zero;
	wire full_zero;
	wire empty_one;
	wire full_one;
	
	//write your code here
	
	QueueCounter clinic_zero (5, 9, (en && (~clinic)) , mode, clk, a0, p0, empty_zero, full_zero);
	
	QueueCounter clinic_one (10, 14, (en && clinic) , mode, clk, a1, p1, empty_one, full_one);
	
	assign ann = (clinic == 0) ? a0 : a1;

	assign print = (clinic == 0) ? p0 : p1;

endmodule
