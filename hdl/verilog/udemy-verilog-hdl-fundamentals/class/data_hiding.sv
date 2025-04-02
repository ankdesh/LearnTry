class data_hide;
  local int x; // Declaring a local variable 'x' within the class. It's only accessible within the class

  // Constructor to initialize the class
  function new(int a);
    x = a; // Assigning the input value 'a' to the local variable 'x'
  endfunction

  // Function to get the value of the local variable 'x'
  function int get_x();
    return x; // Returning the value of 'x'
  endfunction
endclass

module tb;
  data_hide d; // Declaring an object 'd' of the class 'data_hide'

  initial begin
    d = new(10); // Creating an instance of the class 'data_hide' and initializing 'x' to 10
    $display("d.x : %0d", d.get_x()); // Displaying the value of 'x' using the get_x() function
    // d.x is not accessible directly because x is local
  end
endmodule
