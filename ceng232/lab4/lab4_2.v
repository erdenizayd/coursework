`timescale 1ns / 1ps
module IntersectionSimulator(
	input [2:0] mode, //1xx:display, 000:remA, 001:remB, 010:addA, 011:addB
	input [4:0] plateIn,
	input action,
	input clk,
	output reg  greenForA,
	output reg  greenForB,
	output reg 	rushHourWarning,
	output reg [3:0]  hour,
	output reg [5:0]  minute,	
	output reg [5:0]  second,
	output reg	am_pm, //0:am, 1:pm
	output reg [4:0]  numOfCarsA,
	output reg [4:0]  numOfCarsB,
	output reg [6:0]  remainingTime,
	output reg [4:0]  blackListDisplay
	);
	
	//You may write your code anywhere
	
	reg [4:0] roadA [29:0];
	reg [4:0] roadB [29:0];
	reg [4:0] blackList [30:0];
	reg [6:0] current_turnA;
	reg [6:0] current_turnB;
	
	integer i;

	reg [4:0] headA;
	reg [4:0] headB;
	reg [4:0] headBl;
	reg [4:0] tailA;
	reg [4:0] tailB;
	reg [4:0] tailBl;
	reg isA;
	
	initial begin
		greenForA=1;
		greenForB=0;
		rushHourWarning=0;
		hour=6;
		minute=0;
		second=0;
		am_pm=0;
		numOfCarsA=0;
		numOfCarsB=0;
		remainingTime=50;
		blackListDisplay=0;
		current_turnA = 40;
		current_turnB = 50;
		isA = 1;

		headA = 0;
		headB = 0;
		headBl = 0;
		tailA = 0;
		tailB = 0;
		tailBl = 0;
		
		for(i = 0; i <= 29; i = i + 1) 
			roadA[i] <= 5'b00000;
		for(i = 0; i <= 29; i = i + 1)
			roadB[i] <= 5'b00000;
		for(i = 0; i <= 30; i = i + 1)
			blackList[i] <= 5'b00000;
		
	end


	always@(posedge action)
	begin
		if(mode == 3'b000) begin
			if(numOfCarsA > 0) begin
				if(greenForA == 0) begin		
					if(tailBl == 29) begin
						tailBl <= 0;
						blackList[tailBl] <= roadA[headA];
					end
					else begin
						tailBl <= tailBl + 1;
						blackList[tailBl] <= roadA[headA];
					end
				end
				if(headA == 29) begin
					headA = 0;
					numOfCarsA = numOfCarsA - 1;
				end
				else begin
					headA = headA + 1;
					numOfCarsA = numOfCarsA - 1;
				end
			end
		end
		if(mode == 3'b001) begin
			if(numOfCarsB > 0) begin
				if(greenForB == 0) begin				
					if(tailBl == 29) begin
						tailBl <= 0;
						blackList[tailBl] <= roadB[headB];
					end
					else begin
						tailBl <= tailBl + 1;
						blackList[tailBl] <= roadB[headB];
					end
				end
				if(headB == 29) begin
					headB <= 0;
					numOfCarsB = numOfCarsB - 1;
				end
				else begin
					headB <= headB + 1;
					numOfCarsB = numOfCarsB - 1;
				end
			end
		end
		if(mode == 3'b010) begin
			if(tailA == 29) begin
				tailA <= 0;
				roadA[tailA] <= plateIn;
				numOfCarsA = numOfCarsA + 1;
			end
			else begin
				tailA <= tailA + 1;
				roadA[tailA] <= plateIn;
				numOfCarsA = numOfCarsA + 1;
			end
		end
		if(mode == 3'b011) begin
			if(tailB == 29) begin
				tailB <= 0;
				roadB[tailB] <= plateIn;
				numOfCarsB = numOfCarsB + 1;
			end
			else begin
				tailB <= tailB + 1;
				roadB[tailB] <= plateIn;
				numOfCarsB = numOfCarsB + 1;
			end 
		end
		//...
		
	end


	always @(posedge clk)
	begin
		if(mode === 3'b1xx) begin
			if((hour == 9 && am_pm == 0) || (hour == 7 && am_pm == 1))
				rushHourWarning = 0;
			if(headBl == tailBl) begin
				blackListDisplay <= 0;
			end
			else begin
				
				if(headBl == 30) begin
					blackListDisplay <= blackList[headBl];
					headBl = 0;
					
				end
				else begin
					blackListDisplay <= blackList[headBl];
					headBl = headBl + 1;
					if(blackList[headBl] == 5'b00000)
						headBl = 0;
					
				end
			end
		end
		else begin
			headBl = 0;
			if(((hour >= 7) && (hour < 9) && (am_pm == 0)) || ((hour >= 5) && (hour < 7) && (am_pm == 1)) )
				rushHourWarning = 1; 
			else
				rushHourWarning = 0;
			if((hour == 12) && (minute == 0) && (second == 0) && (am_pm == 0)) begin
				tailBl = 0;
				headBl = 0;
			end 

			if(second == 59) begin
				second = 0;
				if(minute == 59) begin
					if(hour == 11) begin
						hour = 12;
						am_pm = ~am_pm;
					end
					else if(hour == 12) begin
						hour = 1;
					end
					else begin
						hour = hour + 1;
					end
					minute = 0;
				end
				else begin
					minute = minute + 1;
				end		
			end
			else begin
				second = second + 1;
			end
			
			if(remainingTime == 1) begin
				if(greenForA == 1) begin
					isA = 0;
					greenForA = 0;
					remainingTime = remainingTime - 1;
				end
				else if(greenForB == 1) begin
					isA = 1;
					greenForB = 0;
					remainingTime = remainingTime - 1;
				end
			end
			else if(remainingTime > 1) begin
				remainingTime = remainingTime - 1;
			end
			else if(remainingTime == 0) begin
				
				if(isA == 1) begin
					if((numOfCarsA >= 0) && (numOfCarsA <= 10)) begin
						current_turnA = current_turnA + 5;
						if((rushHourWarning == 1) && (current_turnA > 60)) begin
							current_turnA = 60;
							
						end
						else if((rushHourWarning == 0) && (current_turnA > 70)) begin
							current_turnA = 70;
						end
					end
					else if(numOfCarsA >= 20) begin
						current_turnA = current_turnA - 5;
						if((rushHourWarning == 1) && (current_turnA < 30)) begin
							current_turnA = 30;
						end
						else if((rushHourWarning == 0) && (current_turnA < 40)) begin
							current_turnA = 40;
						end
					end
					remainingTime = current_turnB;
					greenForA = 1;
				end
				else begin
					if((numOfCarsB >= 0) && (numOfCarsB <= 10)) begin
						current_turnB = current_turnB + 5;
						if((rushHourWarning == 1) && (current_turnB > 70)) begin
							current_turnB = 70;
						end
						else if((rushHourWarning == 0) && (current_turnB > 80)) begin
							current_turnB = 80;
						end
					end
					else if(numOfCarsB >= 20) begin
						current_turnB = current_turnB - 5;
						if((rushHourWarning == 1) && (current_turnB < 40)) begin
							current_turnB = 40;
						end
						else if((rushHourWarning == 0) && (current_turnB < 50)) begin
							current_turnB = 50;
						end
					end
					remainingTime = current_turnA;
					greenForB = 1;
				end
			end
			
			
		end
		
	end


endmodule

