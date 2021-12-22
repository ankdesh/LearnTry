import scala.annotation.tailrec

val args = Array.empty[String] // ("myfile.txt")

val fileName = if (args.length > 0) args(0) else "default.txt"

val x = -10

val res = if (x > 0) x else false


val fileName2 =
  try {
    args.head
  }
  catch {
    case _: NoSuchElementException => "default.txt"
  }
  finally {
    println("Wheeeee")
    "the finally block"
  }

@tailrec
def greet(n: Int, curr: Int = 0): Unit = {
  if (curr < n) {
    println("Hello")
    greet(n, curr + 1)
  }
}

greet(5)
