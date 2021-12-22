import java.io.File
import scala.io.Source

def withFileContents[A](file: File, default: A)(fn: String => A): A = {
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
val hamlet = new File(fileLoc, "hamlet.shkspr")

withFileContents(hamlet, false)(_.trim.endsWith("?"))

withFileContents(hamlet, "")(_.trim.toUpperCase)

// find most common letter
withFileContents(hamlet, 'e') { line =>
  val letters = line.toLowerCase.filterNot(_ == ' ').toSeq
  val grouped = letters.groupBy(identity)
  grouped.maxBy { case (char, seq) => seq.length }._1
}


