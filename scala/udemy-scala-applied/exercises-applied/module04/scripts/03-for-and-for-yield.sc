import java.io.File

for (i <- 1 to 10) println(i * i)

(1 to 10).foreach(i => println(i * i))

for (i <- 1 to 3; j <- 1 to 3) println(i * j)

(1 to 3).foreach(i => (1 to 3).foreach(j => println(i * j)))

for {
  i <- 1 to 3
  j <- 1 to 3
} {
  println(i * j)
}

for (i <- 1 to 10) yield i * i

(1 to 10).map(i => i * i)

for (i <- 1 to 3; j <- 1 to 3) yield i * j

(1 to 3).flatMap(i => (1 to 3).map(j => i * j))

for {
  i <- 1 to 3
  j <- 1 to 3
  k <- 1 to 3
} yield {
  i * j * k
}

(1 to 3).flatMap(i => (1 to 3).flatMap(j => (1 to 3).map(k => i * j * k)))



val fileLoc = new File(getClass.getClassLoader.getResource("").toURI)
val filesHere = new File(fileLoc.getParentFile.getParentFile.getParentFile, "scripts").listFiles()

def fileLines(f: File) = {
  io.Source.fromFile(f).getLines()
}

val forLineLengths =
  for {
    file <- filesHere
    if file.getName.endsWith(".sc")
    line <- fileLines(file)
    trimmed = line.trim
    if trimmed.matches(".*for.*")
  } yield trimmed.length

filesHere.filter(_.getName.endsWith(".sc")).flatMap { file =>
  fileLines(file).filter(_.trim.matches(".*for.*")).map { line =>
    line.trim.length
  }
}

// Notice that the above functions change the inner type
// but outer type remains the same

// for more than just looping:
import scala.concurrent._
import duration._
import ExecutionContext.Implicits.global

val f1 = Future(1.0)
val f2 = Future(2.0)
val f3 = Future(3.0)

val f4 = for {
  v1 <- f1
  v2 <- f2
  v3 <- f3
} yield v1 + v2 + v3

Await.result(f4, 10.seconds)
