import java.io.File
import scala.io.Source

def fileContainsQuestion(file: File): Boolean = {
  val source = Source.fromFile(file)

  try {
    source.getLines().toSeq.headOption.map { line =>
      line.trim.endsWith("?")
    }.getOrElse(false)
  } finally source.close()
}

// change this to the location of your project files
val projectDir = "/home/dwall/dev/Scala/Training/scala-advanced-training/exercises-applied"

val fileLoc = new File(projectDir)

for (name <- Seq("caesar.shkspr", "hamlet.shkspr", "romeo.shkspr")) {
  val file = new File(fileLoc, name)
  println(s"$name ${fileContainsQuestion(file)}")
}


def emphasizeFileContents(file: File): String = {
  val source = Source.fromFile(file)

  try {
    source.getLines().toSeq.headOption.map { line =>
      line.trim.toUpperCase
    }.getOrElse("")
  } finally source.close()
}

for (name <- Seq("caesar.shkspr", "hamlet.shkspr", "romeo.shkspr")) {
  val file = new File(fileLoc, name)
  println(s"$name ${emphasizeFileContents(file)}")
}


