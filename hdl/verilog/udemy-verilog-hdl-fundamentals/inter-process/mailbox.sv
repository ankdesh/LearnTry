module tb;
  
  mailbox #(integer) mbx;
  integer i;
  integer data;
  
  initial begin
    mbx = new();
    
    
    fork
    
      begin
        
        for(i =0; i <20; i++) begin
          mbx.put(i);
          $display("Data Send : %0d",i);
          #10;
        end
        
      end
     
      begin
        
      forever begin
        mbx.get(data);
        $display("Value rcvd : %0d",data);
        #10;
      end
        
      end
  
  
    join
  
  
  end
  
  
endmodule