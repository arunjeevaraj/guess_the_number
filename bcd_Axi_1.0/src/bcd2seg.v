`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/23/2017 08:38:23 AM
// Design Name: 
// Module Name: bcd2seg
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


module bcd2seg(
    input [3:0] bcd_in,
    output [6:0] seg_out,
    output an_sel
    );
    
reg [6:0] seg_out;

assign an_sel = 0;

always @ (bcd_in)
begin
    case(bcd_in)
        4'b0000: seg_out = 1;
        4'b0001: seg_out = 79;
        4'b0010: seg_out = 18;
        4'b0011: seg_out = 6;
        4'b0100: seg_out = 76;
        4'b0101: seg_out = 36;
        4'b0110: seg_out = 32;
        4'b0111: seg_out = 15;
        4'b1000: seg_out = 0;
        4'b1001: seg_out = 4;  
        default: seg_out = 0;
    endcase
end
    
endmodule
