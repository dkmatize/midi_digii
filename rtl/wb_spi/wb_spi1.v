//-----------------------------------------------------------------
// SPI Master
//-----------------------------------------------------------------

module wb_spi1(
	input               clk,
	input               reset,
	// Wishbone bus
	input      [31:0]   wb_adr_i,
	input      [31:0]   wb_dat_i,
	output reg [31:0]   wb_dat_o,
	input      [ 3:0]   wb_sel_i,
	input               wb_cyc_i,
	input               wb_stb_i,
	output              wb_ack_o,
	input               wb_we_i,
	// SPI 
	output              spi1_sck,
	output              spi1_mosi,
	input               spi1_miso,
	output reg   [7:0]  spi1_cs
);


	reg  ack;
	assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

	wire wb_rd = wb_stb_i & wb_cyc_i & ~ack & ~wb_we_i;
	wire wb_wr = wb_stb_i & wb_cyc_i & ~ack & wb_we_i;

	
	reg [3:0] bitcount1;
	reg ilatch;
	reg run1;

	reg sck1;

	//prescaler registers for sclk
	reg [7:0] prescaler1;
	reg [7:0] divisor1;

	//data shift register
	reg [7:0] sreg1;

	assign spi1_sck = sck1;
	assign spi1_mosi = sreg1[7];

	always @(posedge clk) begin
		if (reset == 1'b1) begin
			ack      <= 0;
			sck1 <= 1'b0;
			bitcount1 <= 4'b0000;
			run1 <= 1'b0;
			prescaler1 <= 8'h00;
			divisor1 <= 8'hff;
		end else begin
			prescaler1 <= prescaler1 + 1;
			if (prescaler1 == divisor1) begin
				prescaler1 <= 8'h00;
				if (run1 == 1'b1) begin
					sck1 <= ~sck1;
					if(sck1 == 1'b1) begin
						bitcount1 <= bitcount1 + 1;
						if(bitcount1 == 4'b1111) begin
							run1 <= 1'b0;
							spi1_cs <= 7'b0000000; 
						end
						
						sreg1 [7:0] <= {sreg1[6:0], ilatch};
					end else begin
						ilatch <= spi1_miso;
					end
				end
			end

			ack <= wb_stb_i & wb_cyc_i;
			
			if (wb_rd) begin           // read cycle
				case (wb_adr_i[5:2])
					4'b0000: wb_dat_o <= sreg1;
					4'b0001: wb_dat_o <= {7'b0000000 , run1};
				endcase
			end
			
			
			if (wb_wr) begin // write cycle
				case (wb_adr_i[5:2])
					4'b0000: begin
							sreg1    <=  wb_dat_i[7:0];
							run1     <=  1'b1;
						end
					4'b0010:
							spi1_cs  <=  wb_dat_i[7:0];
					4'b0011: 
							divisor1 <=  wb_dat_i[7:0];
				endcase
			end
		end
	end


endmodule
