class rand_class;
  rand bit [3:0] a; // Declaring a 4-bit random variable 'a'
  rand bit [3:0] b; // Declaring a 4-bit random variable 'b'
  rand bit [31:0] c; // Declaring a 32-bit random variable 'c'

  // Constructor for the class
  function new();
  endfunction
endclass

module tb;
  rand_class rc; // Declaring an object 'rc' of the class 'rand_class'

  initial begin
    rc = new(); // Creating an instance of the class 'rand_class'
    $display("Random values:");
    for (int i = 0; i < 10; i++) begin // Loop to generate and display 10 sets of random values
      rc.randomize(); // Randomizing the values of 'a', 'b', and 'c'
      $display("a = %0d, b = %0d, c = %0d", rc.a, rc.b, rc.c); // Displaying the randomized values
    end
  end
endmodule
