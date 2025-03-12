module hi (
    input clk, 
    output reg EN, 
    RW, 
    RS,
	output reg [7:0] data,
);

parameter MS = 50_000;
parameter WRITE = 0, WAIT = 1;

reg state = WRITE;
reg [7:0] instructions = 0;
reg [31:0] counter = 0;

initial begin
    EN = 0;
    RW = 0;
    RS = 0;
    data = 0;
end

//analogo a parte sequencial da maquina de estados
always @(posedge clk) begin
    case (state) 
        WRITE: begin 
            if(counter == MS -1) begin
                counter <= 0;
                state <= WAIT;
            end
            else counter <= counter + 1;
        end
        WAIT: 
            if(counter == MS -1) begin
                counter <= 0;
                state <= WRITE;
                if(instructions < 20) instructions <= instructions + 1;
            end
            else begin
                counter <= counter + 1;
            end
        default: begin end 
    endcase
end

//analogo a parte combinacional
always @(posedge clk ) begin
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

        5: 
        default: begin data <= 8'h02; RS <= 0; end
    endcase
end

endmodule
