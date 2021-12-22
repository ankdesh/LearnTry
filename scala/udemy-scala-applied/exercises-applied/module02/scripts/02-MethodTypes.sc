def max(x: Int, y: Int): Int =
  if (x > y) x else y

def min(x: Int, y: Int) =
  if (x < y) x else y

def sayHi(name: String): Unit =
  println(s"hello $name")

sayHi("Scala class")

def procedureSyntax(name: String) {
  println(s"hello $name")
}



