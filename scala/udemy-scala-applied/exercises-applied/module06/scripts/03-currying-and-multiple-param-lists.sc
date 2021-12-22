val add3: (Int, Int, Int) => Int = (a, b, c) => a + b + c

val add3curried = add3.curried

val add3c: Int => Int => Int => Int = a => b => c => a + b + c

add3(1,2,3)
add3curried(1)(2)(3)
add3c(1)(2)(3)

add3c.apply(1).apply(2).apply(3)

def add3method(a: Int)(b: Int)(c: Int) = a + b + c
add3method(1)(2)(3)

add3method { 1 } { 2 } { 3 }
