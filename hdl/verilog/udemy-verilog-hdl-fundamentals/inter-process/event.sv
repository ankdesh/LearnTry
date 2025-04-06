module tb;
  
  event a;
  
  
  initial begin
  
  
  fork
  
  begin
  #20;
  -> a;
  end
  
  
  begin
    @(a.triggered); //@() , wait
    $display("Event Triggered at %0t",$time);
  
  end
  
  
  join
  
  
  end
  
endmodule
