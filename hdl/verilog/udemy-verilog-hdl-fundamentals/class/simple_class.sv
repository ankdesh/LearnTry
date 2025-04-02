class temp;

  function bit [8:0] add(input bit [7:0] a, input bit [7:0] b);
    return a + b;
  endfunction
endclass

module tb;

  temp t;
  bit [8:0] result;

  initial begin
    $dumpfile("dump.vcd");
    $dumpvars();
    t = new();
    #5;
    result = t.add(8'h12, 8'h23);
    #10;
    $display("Result : %0d", result);
  end
endmodule
