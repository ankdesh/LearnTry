module sum_product ();
    integer a,b;
    integer sum_int;

    real x,y;
    real prod_real;

    initial begin
        a = 3;
        b = 9;
        sum_int = a+b;
        $display("\n a = %0d, b = %0d, sum = %0d",a,b,sum_int);

        x = 99.37;
        y = -33.4;
        prod_real = x * y;
        $display("\n x = %0.2f, y = %0.2f, prod = %0.2f",x,y,prod_real);
    end


endmodule