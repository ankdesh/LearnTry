import java.io.{File, PrintWriter}
// an expression

val x = 1 + 2

// a statement

println(x)

// since everything has a return type

val un = println(x)


un == ()


class WriterOutput(writer: PrintWriter) {
  def write(s: String): Unit = writer.println(s)
}

val ex1 = new PrintWriter(new File("ex1.txt"))

val out1 = new WriterOutput(ex1)

out1.write("Hello")
out1.write("to")
out1.write("you")

ex1.close()


class WriterOutput2(writer: PrintWriter) {
  def write(s: String): WriterOutput2 = {
    writer.println(s)
    this
  }
}

val ex2 = new PrintWriter(new File("ex2.txt"))

val out2 = new WriterOutput2(ex2)

out2.write("Hello").write("to").write("you")

ex2.close()
