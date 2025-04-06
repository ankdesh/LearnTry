`timescale 1us/1ns

module xor4(
  input [3:0] a,b,
  output [3:0] y
 
);

assign y = a ^ b;
endmodule

class transaction;
  randc bit [3:0] a;
  randc bit [3:0] b;
  bit [3:0] y;
endclass
 
class generator;
  transaction t;
  mailbox #(transaction) mbx;
  event done;
  integer i;
  
  function new(mailbox #(transaction) mbx);
    this.mbx = mbx;
  endfunction
  
  task run();
    t = new();
    for(i = 0; i < 25; i++) begin
      t.randomize();
      mbx.put(t);
      $display("[GEN] : Data send to Driver at %d: a=%0d, b=%0d", $time, t.a, t.b);
      #1;
    end
    -> done;
  endtask
 
endclass
 
 
interface xor4_intf();
  logic [3:0] a;
  logic [3:0] b;
  logic [3:0] y;
  
endinterface
 
 
class driver;
  
  transaction t;
  mailbox #(transaction) mbx;
  virtual xor4_intf vif;

  function new(mailbox #(transaction) mbx);
    this.mbx = mbx;    
  endfunction
  
  task run();
    t = new();
    forever begin
      mbx.get(t);
      vif.a = t.a;
      vif.b = t.b;
      #1; // Add a small delay to allow the DUT to react
      //t.y = vif.y; // Sample the value of vif.y
      $display("[DRV] : Trigger Interface, a=%0d, b=%0d, y=%0d", t.a, t.b, t.y);
      #10; // Add a delay to match the generator delay
    end
  endtask
  
endclass
 
module tb;
  
  generator gen;
  driver drv;
  mailbox #(transaction) gdmbx;
  
  xor4_intf vif();
  
  xor4 dut (vif.a,vif.b, vif.y);
  
  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, tb.vif, tb.dut);
  end
  
  
  initial begin 
    gdmbx = new();
    gen = new(gdmbx);
    drv = new(gdmbx);
    
    drv.vif = vif;
    
    fork
      gen.run();
      drv.run();
    join_any
    wait(gen.done.triggered);
  end
  
  endmodule
