class base;
  local int x; // Declaring a local integer variable 'x'

  // Constructor for the base class
  function new(int a);
    x = a; // Initialize 'x' with the value of 'a'
  endfunction

  // Function to get the value of 'x'
  function int get_x();
    return x; // Return the value of 'x'
  endfunction
endclass

// Derived class inheriting from the base class
class derived extends base;
  // Constructor for the derived class
  function new(int a);
    super.new(a); // Call the constructor of the base class
  endfunction
endclass

module tb;
  base b; // Declare an object of the base class
  derived d; // Declare an object of the derived class
  initial begin
    b = new(10); // Create an object of the base class and initialize it with 10
    d = new(20); // Create an object of the derived class and initialize it with 20
    $display("b.x : %0d", b.get_x()); // Display the value of 'x' in the base class object
    $display("d.x : %0d", d.get_x()); // Display the value of 'x' in the derived class object
  end
endmodule
