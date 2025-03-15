module logical ();
    reg [2:0] a = 3'b111;
    reg [2:0] b = 3'b110;
    reg [2:0] result;

    initial 
    begin
        $monitor ("%b %b %b",a,b, result);
    end

    initial 
    begin
        $dumpfile("dump.vcd");
        $dumpvars(0,logical);
        #1 result = ~b;
        #1 result = a & b;
        #1 result = a | b;
    end


endmodule