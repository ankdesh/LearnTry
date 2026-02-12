module top(input [3:0] a,
            input [3:0]b,
            output [3:0]y);
assign y = a & b;

endmodule

class transaction;
  bit [3:0] a;
  bit [3:0] b;
  bit [3:0] y;
 
endclass
 
interface top_intf();
  logic [3:0] a;
  logic [3:0] b;
  logic [3:0] y;
endinterface
 
class monitor;
  transaction t;
  mailbox #(transaction) mbx;
  
  virtual top_intf vif;
  
  function new(mailbox #(transaction) mbx);
    this.mbx = mbx;
  endfunction
  
  task run();
    t = new();
    t.a = vif.a;
    t.b = vif.b;
    t.y = vif.y;
    mbx.put(t);
    $display("[MON] : data send to Scoreboard");
    #10;
  endtask
 
endclass
 
 
class scoreboard;
  transaction t;
  mailbox #(transaction) mbx;
  bit [3:0] temp;
  
  function new(mailbox #(transaction) mbx);
    this.mbx = mbx;
    endfunction
  
  task run();
    t = new();
    forever begin
      mbx.get(t);
      temp = t.a & t.b;
      if(t.y == temp)
        begin
          $display("[SCO] : Test Passed");
          $display("[SCO] : a : %b and b : %b gives temp : %b and y : %b ",t.a, t.b, temp, t.y);
        end
      else
        begin
          $display("[SCO] : Test Failed");
        end
      #10;
    end
  endtask
  
endclass
 
module tb;
  
  top_intf vif();
  monitor mon;
  scoreboard sco;
  mailbox #(transaction) msmbx;
  
  
  top dut (.a(vif.a), .b(vif.b), .y(vif.y));
  
  initial begin
    vif.a = $random();
    vif.b = $random();
  end
  
  initial begin
    msmbx = new();
    mon = new(msmbx);
    sco = new(msmbx);
    
    mon.vif = vif;
    
    fork 
      mon.run();  
      sco.run();
    join
  
  end
  
  
  
  
endmodule