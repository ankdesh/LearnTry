val pf1: PartialFunction[Int, Int] = {
  case x: Int if x > 0 => x + x
  case x => x * -1
}

val fn1: Int => Int = pf1  // upcast

val nums = (-5 to 5).toList

nums.map(pf1)

val pf2: PartialFunction[Int, Int] = {
  case x: Int if x > 0 => x + x
}

// nums.map(pf2)
pf2.isDefinedAt(5)
pf2.isDefinedAt(-5)

nums.collect(pf2)

val a = 4

a match {
  case 4 => "It's four!"
}

try (1 / 0)
catch {
  case ae: ArithmeticException => 0
}
