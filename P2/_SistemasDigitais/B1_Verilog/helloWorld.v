module aula(
	output reg[7:0] data,
	output reg EN, RW, RS,

	input [4:0] a,
    input [4:0] b,
	input clk
);

initial begin
	data = 0;
	EN = 0; //Enable
	RW = 0; //Read/Write
	RS = 0;//
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
                data <= a + b;
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
        //Botão Ligar
		0: begin data <= 8'h38; RS <= 0; end //Habilita o modo de 8 bits, adiciona a segunda linha
		1: begin data <= 8'h0E; RS <= 0; end //Display ON, Cursos ON, Blink OFF
		2: begin data <= 8'h01; RS <= 0; end //Clear
		3: begin data <= 8'h02; RS <= 0; end //Cursor Home
		4: begin data <= 8'h06; RS <= 0; end //Não sei pra que serve isso
		
		5: begin data <= 8'h48; RS <= 1; end //H

		
		default: begin data <= 8'h02; RS <= 0; end
	endcase

end


endmodule 