1 -> "one"

2.->("two")

ArrowAssoc(3).->("three")


// easy map iteration

val mapToRiches = Map(
  1 -> "steal underpants",
  2 -> "???",
  3 -> "profit"
)

for ((step, instruction) <- mapToRiches) {
  println(s"Step $step - $instruction")
}

