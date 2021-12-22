def multiplyMethod(a: Int, b: Int): Int = a * b

val multiplyFunction: (Int, Int) => Int = (a, b) => a * b

multiplyMethod(2, 3)

multiplyFunction(2, 3)


val nums = (1 to 5).toList

nums.map(x => x * x)

nums.map(x => x * 3)

nums.map(x => x % 2 == 0)
