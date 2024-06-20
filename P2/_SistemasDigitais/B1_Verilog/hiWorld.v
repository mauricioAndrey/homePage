module aula(
	output reg[7:0] data,
	output reg EN, RW, RS,
	
	input clk
);

initial begin
	data = 0;
	EN = 0;
	RW = 0;
	RS = 0;
end

reg [31:0] counter = 0;
parameter MS = 50_000;
parameter WRITE = 0, WAIT = 1;
reg [3:0] state = WRITE;

reg [7:0] instructions = 0;

always @(posedge clk) begin
	case (state)
		WRITE: begin
			if(counter == MS - 1) begin
				state <= WAIT;
				counter <= 0;
			end else begin
				counter <= counter + 1;
			end
		end
		WAIT: begin
			if(counter == MS - 1) begin
				state <= WRITE;
				counter <= 0;
				if(instructions < 20) instructions <= instructions + 1;
			end else begin
				counter <= counter + 1;
			end
		
		end
		default : begin end
	endcase
end


always @(posedge clk) begin
	case (state)
		WRITE: EN <= 1;
		WAIT: EN <= 0;
		default: EN <= EN;
	endcase
	
	case (instructions)
		0: begin data <= 8'h38; RS <= 0; end
		1: begin data <= 8'h0E; RS <= 0; end
		2: begin data <= 8'h01; RS <= 0; end
		3: begin data <= 8'h02; RS <= 0; end
		4: begin data <= 8'h06; RS <= 0; end
		
		5: begin data <= 8'h48; RS <= 1; end
		6: begin data <= 8'h65; RS <= 1; end
		7: begin data <= 8'h6C; RS <= 1; end
		8: begin data <= 8'h6C; RS <= 1; end
		9: begin data <= 8'h6F; RS <= 1; end
		
		10:begin data <= 8'hC0; RS <= 0; end
		
		11: begin data <= 8'h57; RS <= 1; end
	   12: begin data <= 8'h6F; RS <= 1; end
		13: begin data <= 8'h72; RS <= 1; end
		14: begin data <= 8'h6C; RS <= 1; end
		15: begin data <= 8'h64; RS <= 1; end
		16: begin data <= 8'h21; RS <= 1; end
		17: begin data <= 8'h21; RS <= 1; end
		18: begin data <= 8'h3a; RS <= 1; end
		19: begin data <= 8'h44; RS <= 1; end
		
		
		
		default: begin data <= 8'h02; RS <= 0; end
	endcase
end



endmodule 