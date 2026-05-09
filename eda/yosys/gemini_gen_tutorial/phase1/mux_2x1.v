module mux_2x1 (
    input a, b, sel,
    output out
);
    wire sel_n;
    wire out_0;
    wire out_1;

    // 4 Gates Instantiation
    not n1(sel_n, sel);       // Gate 1: Invert select
    and a1(out_0, a, sel_n);  // Gate 2: AND input 'a' with negated select
    and a2(out_1, b, sel);    // Gate 3: AND input 'b' with select
    or  o1(out, out_0, out_1); // Gate 4: Combine results
endmodule

