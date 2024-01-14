// Copyright (C) 2018  Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License 
// Subscription Agreement, the Intel Quartus Prime License Agreement,
// the Intel FPGA IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Intel and sold by Intel or its authorized distributors.  Please
// refer to the applicable agreement for further details.

module Exo1_leds_sys
(
// {ALTERA_ARGS_BEGIN} DO NOT REMOVE THIS LINE!

	altera_reserved_tck,
	altera_reserved_tdi,
	altera_reserved_tdo,
	altera_reserved_tms,
	clk_clk,
	pio_0_external_connection_export,
	pio_1_external_connection_export,
	pio_2_external_connection_export,
	reset_reset_n
// {ALTERA_ARGS_END} DO NOT REMOVE THIS LINE!

);

// {ALTERA_IO_BEGIN} DO NOT REMOVE THIS LINE!
input			altera_reserved_tck;
input			altera_reserved_tdi;
output			altera_reserved_tdo;
input			altera_reserved_tms;
input			clk_clk;
output	[7:0]	pio_0_external_connection_export;
input			pio_1_external_connection_export;
input	[7:0]	pio_2_external_connection_export;
input			reset_reset_n;

// {ALTERA_IO_END} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_BEGIN} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_END} DO NOT REMOVE THIS LINE!
endmodule
