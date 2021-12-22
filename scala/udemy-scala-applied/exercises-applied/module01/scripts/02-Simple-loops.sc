var x = 0

while (x < 10) {
  println(s"the square of $x is ${x * x}")
  x += 1
}

x = 0
do {
  println(s"the square of $x is ${x * x}")
  x += 1
} while (x < 10)

