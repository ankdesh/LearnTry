import scala.annotation.tailrec

@tailrec
def fruitLoop(pred: () => Boolean)(body: () => Unit): Unit = {
  if (pred()) {
    body()
    fruitLoop(pred)(body)
  }
}

var x = 0

fruitLoop(() => x < 5) { () =>
  println(x * x)
  x += 1
}


@tailrec
def fruityLoop(pred: => Boolean)(body: => Unit): Unit = {
  if (pred) {
    body
    fruityLoop(pred)(body)
  }
}

var y = 0
fruityLoop(y < 5) {
  println(y * y)
  y += 1
}
