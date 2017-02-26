`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/04/2016 09:25:36 AM
// Design Name: 
// Module Name: test
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test(
    input [1:0] sw,
    output [3:0] led
    );
    
reg [3:0] H;
assign led = H;
always @(sw)
    case(sw)
    2'b00: H=4'b0001; // Note that 4'b0001 means "4" bits of "0001"
    2'b01: H=4'b0010;
    2'b10: H=4'b0100;
    2'b11: H=4'b1000;
    endcase

endmodule
