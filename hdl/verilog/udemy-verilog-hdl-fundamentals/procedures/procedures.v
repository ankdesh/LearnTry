module procedure ();
    reg x = 1;
    reg y = 0;
    reg z = 0'b1;    

always @(z) 
begin
    $display("%b %b %b",x,y,z);
end

initial 
begin
    $dumpfile("dump.vcd");
    $dumpvars(0,procedure);
    #20 z = ~z;
    #30 z = ~z;
    #40 z = ~z;

end

endmodule