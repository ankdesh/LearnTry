import java.io.File
import scala.io.Source

def withFileContents[A](file: File, fn: String => A, default: A): A = {
  val source = Source.fromFile(file)

  try {
    source.getLines().toSeq.headOption.map { line =>
      fn(line)
    }.getOrElse(default)
  } finally source.close()
}

// change this to the location of your project files
val projectDir = "/home/dwall/dev/Scala/Training/scala-advanced-training/exercises-applied"

val fileLoc = new File(projectDir)

for (name <- Seq("caesar.shkspr", "hamlet.shkspr", "romeo.shkspr")) {
  val file = new File(fileLoc, name)
  val result = withFileContents(file, _.trim.endsWith("?"), false)
  println(s"$name $result")
}


for (name <- Seq("caesar.shkspr", "hamlet.shkspr", "romeo.shkspr")) {
  val file = new File(fileLoc, name)
  val result = withFileContents(file, _.trim.toUpperCase, "")
  println(s"$name $result")
}

val hamlet = new File(fileLoc, "hamlet.shkspr")

// find most common letter
withFileContents(hamlet, { line =>
  val letters = line.toLowerCase.filterNot(_ == ' ').toSeq
  val grouped = letters.groupBy(identity)
  grouped.maxBy { case (char, seq) => seq.length }._1
}, 'e')

