def greet(name: String): String =
  "hello" + name   // here we use the parameter name

// we can also use it from outside of the class

greet("Fred")

greet(name = "Fred")

// idiomatically this is good for flags:

def thingy(isCold: Boolean, isBroken: Boolean): Unit = {}

thingy(true, false) // doesn't tell us much
thingy(isCold = true, isBroken = false) // is much more readable

// and you can change up the order

thingy(isBroken = false, isCold = true)


def gravity = 9.81  // meters/sec

def force(mass: Double = 1, acceleration: Double = gravity) =
  mass * acceleration

force()
force(12)

force(acceleration = 2 * gravity)
force(acceleration = gravity / 13.0, mass = 100)

def factSeq(n: Int, acc: List[Long] = List(1L), ct: Int = 2): List[Long] = {
  if (ct > n) acc else factSeq(n, acc = ct * acc.head :: acc, ct = ct + 1)
}