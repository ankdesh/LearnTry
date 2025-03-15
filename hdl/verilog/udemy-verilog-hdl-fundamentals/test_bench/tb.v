module moduleName ();
    
    reg [7:0] a_tb;
    reg [7:0] b_tb;
    wire [8:0] sum_tb;

    adder_8bit Add8(
        .a(a_tb),
        .b(b_tb),
        .sum(sum_tb)
    );

    initial 
    begin
        $monitor ("%d + %d = %d",a_tb,b_tb,sum_tb);
    end

    initial 
    begin
        $dumpfile("dump.vcd");
        $dumpvars(0,logical);
        #1 a_tb = 1;
        #1 b_tb = 10;
        #1 a_tb = 255; b_tb = 255;
    end

endmodule