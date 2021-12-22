val x = 1

x match {
  case 1 => println("it's one")
  case 2 => println("it's two")
  case _ => println("it's something else")
}

val res = x match {
  case 1 => "one"
  case 2 => "two"
  case _ => "something else"
}


val n = -1

n match {
  case 0 => "It's zero"
  case v if n > 0 => s"It's positive $v"
  case v => s"It's negative ${v.abs}"
}


def matchIt(x: Any): String = x match {
  case "Hello" => "Well, hello back"
  case 1 :: rest => s"A list beginning with 1, rest is $rest"
  case Nil => "The empty list"
  case 5 => "The number 5"
  case _: List[_] => "Some kind of list, not empty and not starting with 1"
}


matchIt(5)
matchIt(List(1,2,3))
matchIt(List(1))
matchIt(List(2,3))
matchIt(Nil)

matchIt(2.0)