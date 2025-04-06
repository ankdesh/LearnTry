class process1;
  
  task run();
    #6;
    $display("Process 1 complete at %0t",$time);
  endtask
  
 
endclass
 
 
class process2;
  
  task run();
    #3; 
    $display("Process 2 complete at %0t",$time);
  endtask
  
 
endclass
 
 
module tb;
  
  process1 p1;
  process2 p2;
  
  initial begin
    p1 = new();
    p2 = new();
    
    fork
      p1.run();
      p2.run();
    join //join_none
    
 
    $display("All processes completed at %0t",$time);
    
  end
  
  
  
  
  
  
endmodule