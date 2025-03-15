
`timescale 1us/1ns   // mandatory because we have delays
module built_in_gates(
    // Declare module inputs
    input a, b, c, d,
    // Declare module outputs
    output o1, o2, o3, o4, o5, o6, o7, o8, o9, o10
    );

    // Gates without delays
    and  and1  (o1, a, b);
    nand nand1 (o2, c, d);
    or   or1   (o3, a, b, c, d);
    nor  nor1  (o4, c, d);
    xor  xor1  (o5, a, b, c);
    xnor xnor1 (o6, b, d);
    buf  buf1  (o7, c);
    not  not1  (o8, d);
    
    // Gates with delays
    buf #0.1 buf_dly  (o9, c);     // the delay requires timescale
    and #0.2 and_dly  (o10, a, b); // compare wave with and1
  
endmodule


