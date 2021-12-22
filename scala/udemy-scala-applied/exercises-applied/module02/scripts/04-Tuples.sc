def sumAndDifference(a: Int, b: Int): (Int, Int) = {
  val sum = a + b
  val difference = a - b
  (sum, difference)
}

val res = sumAndDifference(10, 5)

res._1
res._2

val (sm, df) = sumAndDifference(10, 5)

val (a,b,c,d,e) = (0, 'u', 8, 1, "too")


