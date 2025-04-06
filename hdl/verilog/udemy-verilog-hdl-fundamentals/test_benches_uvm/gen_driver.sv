class transaction;
randc bit [3:0] a;
randc bit [3:0] b;
endclass
 
 
 
 
class generator;
transaction t;
mailbox #(transaction)mbx ;
event done;
integer i;
 
function new(mailbox  #(transaction) mbx);
this.mbx = mbx;
endfunction
 
task main();
for(i = 0; i <10; i++)begin
t = new();
t.randomize();
mbx.put(t);
$display("[GEN] :  Send Data to Driver %d %d", t.a, t.b);
#1;
end
->done;
endtask
endclass
 
 
class driver;
mailbox  #(transaction) mbx;
transaction t;
 
function new(mailbox  #(transaction) mbx);
this.mbx = mbx;
endfunction
 
task main();
forever begin
t = new();
mbx.get(t);
$display("[DRV] : Rcvd Data from Generator %d %d", t.a, t.b);
#1;
end
endtask
 
 
endclass
 
 
 
 
 
module tb();
 
transaction t;
generator gen;
driver drv;
mailbox  #(transaction) mbx;
 
initial begin
mbx = new();
gen = new(mbx);
drv = new(mbx);
 
fork
gen.main();
drv.main();
join_any
wait(gen.done.triggered);
end
 
 
endmodule