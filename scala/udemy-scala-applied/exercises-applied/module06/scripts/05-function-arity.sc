val sq: Int => Int = x => x * x  // Function1[Int, Int]
val add: (Int, Int) => Int = (a, b) => a + b  // Function2[Int, Int, Int]
val mult3: (Int, Int, Int) => Int = _ * _ * _ // Function3[Int, Int, Int, Int]


import scala.util.Random
val makeARandom: () => Double = () => Random.nextDouble()

makeARandom()
makeARandom()
