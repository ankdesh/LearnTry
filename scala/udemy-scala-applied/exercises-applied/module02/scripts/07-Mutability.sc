// Arrays are Mutable:

val arr = Array("scooby", "dooby", "doo")

arr(0) = "scrappy"
arr(1) = "dappy"

arr.mkString(" ")

// Lists and Vectors are not mutable

val xs1 = List(1,2,3)
val xs2 = 0 :: xs1

var xs3 = List(4,5,6)
xs3 = xs2 ::: xs3  // because it's a var

// Sets may be either:

import scala.collection._

val s1 = mutable.Set(1,2,3)
var s2 = immutable.Set(1,2,3)

// += on both types:

s1 += 4  // calls += on mutable.Set
s1

s2 += 4  // turns into s2 = s2 + 4
s2

// Maps also may be either

val m1 = mutable.Map('a' -> 1, 'b' -> 2, 'c' -> 3)

var m2 = immutable.Map('d' -> 4, 'e' -> 5, 'f' -> 6)

m1 ++= m2
m2 += 'g' -> 7
m2

