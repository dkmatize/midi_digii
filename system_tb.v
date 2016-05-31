//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 20;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
wire       led;
reg [7:0] data;
wire [7:0] gpio_io;
wire [7:0] spi_mosi;
wire [7:0] spi_cs;
wire [7:0] gpio_i;
reg [7:0] gpio_dir;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;

genvar i;
	generate
		for (i=0; i<8; i=i+1) begin: gpio_tris
		assign gpio_io[i]= ~(gpio_dir[i]) ? data[i] : 1'bz;
		assign gpio_i[i] = gpio_io[i];
		end
	endgenerate

//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------
system #(
	.clk_freq(           clk_freq         ),
	.uart_baud_rate(     uart_baud_rate   )
) dut  (
	.clk(          clk    ),
	// Debug
	.rst(          rst    ),
	.led(          led    ),
	// Uart
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  ),
	.gpio_io( gpio_io )
);

/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;

/* Simulation setup */
initial begin



	$dumpfile("system_tb.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, dut,data,gpio_io);
	//$dumpvars(-1,clk,rst,uart_txd);
	// reset
	#0  rst <= 0;
	#0  gpio_dir <= 8'h00;
	#1000 rst <= 1;
	#3000
	#2000 gpio_dir <= 8'hF0;
	#2000;	
	#2000 data <= 8'hAA;
	#100000;
	#2000 data <= 8'h0A;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hAA;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;	
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;
	#2000 data <= 8'hFF;
	#1000;
	#2000 data <= 8'h00;
	#1000;		
	#(tck*20000) $finish;
end



endmodule
