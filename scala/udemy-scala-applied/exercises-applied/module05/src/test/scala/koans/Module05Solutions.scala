
/* Copyright (C) 2010-2018 Escalate Software, LLC. All rights reserved. */

package koans
import org.scalatest.Matchers
import org.scalatest.SeveredStackTraces
import support.KoanSuite
import java.net.{MalformedURLException, URL}

class Module05Solutions extends KoanSuite with Matchers with SeveredStackTraces {

  test ("Multiply numbers") {
    var multiplier = 3

    // Uncomment the tests below, then write a local function, mult, to satisfy the tests below.
    // Remember that local functions can access variables from the method space without the
    // need to pass them in. The function should multiply the argument passed in by the multiplier var

    def mult(x: Int): Int = x * multiplier

    // UNCOMMENT TESTS
    mult(5) should be (15)
    mult(3) should be (9)

    // why do the results of mult change here?
    multiplier = 5
    mult(5) should be (25)
    mult(3) should be (15)
  }

  test ("Filter numbers") {
    val allNumbers = List(0,1,2,3,4,5,6,7)
    
    // alter the two filters below to filter only odd and even numbers out of the list respectively,
    // to make the tests pass.
    // Just like in Java, % is the modulo operator

    val onlyOdd = allNumbers.filter(x => x % 2 != 0)
    val onlyEven = allNumbers.filter(x => x % 2 == 0)

    onlyOdd should be (List(1,3,5,7))
    onlyEven should be (List(0,2,4,6))
  }

  test ("Function with placeholder syntax") {
    // using placeholder syntax, define a val "mult" that multiplies 2 Ints together, then uncomment
    // the tests below and make sure they pass

    val mult = (_: Int) * (_: Int)

    mult(2, 4) should be (8)
    mult(10, 10) should be (100)
  }

  test ("Bounds limiter partial function") {
    def boundToLimits(lower: Int, v: Int, upper: Int) : Int = {
      // if the upper is higher than the lower, reverse the bounds
      val l = lower min upper
      val u = lower max upper

      if (v < l) l
      else if (v > u) u
      else v
    }

    // tests - make sure the bound to limits works
    boundToLimits(10, 5, 90) should be (10)
    boundToLimits(10, 50, 90) should be (50)
    boundToLimits(10, 100, 90) should be (90)

    // now create a partially applied function from the above called waterAsLiquid with lower bounds of 0
    // and upper bounds of 100, but with the middle value (to test) not yet bound (use a placeholder)
    // Then uncomment the tests below and make sure they pass

    val waterAsLiquid = boundToLimits(0, _: Int, 100)

    waterAsLiquid(34) should be (34)
    waterAsLiquid(-10) should be (0)
    waterAsLiquid(400) should be (100)
  }

  test ("Multiply variable number of arguments") {
    // create a multipleDoubles method to satisfy the tests below, uncomment the tests and run them
    // to ensure it works

    def multiplyDoubles(dbls: Double*): Double = {
      if (dbls.isEmpty) 1.0
      else dbls.head * multiplyDoubles(dbls.tail: _*)
    }

    multiplyDoubles(1.0, 2.0, 3.0) should be (6.0 +- 0.00001)
    multiplyDoubles(1.1, 2.2, 3.3, 4.4, 5.5, 6.6) should be (1275.52392 +- 0.00001)
    multiplyDoubles() should be (1.0)

    // extra credit, can you re-write the multiplyDoubles method to work without needing to use any vars?
  }

  test ("Recurse with varargs") {
    // write a listOfLists recursive method that takes a number of strings as varargs and then
    // creates a list of lists of strings, with one less string in each, so for example:
    //
    // listOfLists("3","2","1") should give back: List(List("3","2","1"), List("2","1"), List("1"))
    // If you have trouble with the recursive call, check the argument expansion slide for help
    // Uncomment the tests below to make sure the method works.

    def listOfLists(theList: String*): List[List[String]] = {
      if (theList.isEmpty) Nil
      else theList.toList :: listOfLists(theList.tail: _*)
    }

    listOfLists("Hello", "World") should be (List(List("Hello", "World"), List("World")))
    listOfLists("Hello", "There", "World") should be (List(List("Hello", "There", "World"), List("There", "World"), List("World")))  

    // is this implementation of listOfLists properly recursive? If not, why not?
  }

  test ("URL cleaner") {
    def urlClean(urlAsString : String) : URL = {
      try {
        new URL(urlAsString)
      }
      catch {
        case ex: MalformedURLException => new URL("http://badurl.com")
      }
    }

    // fix the method above to catch a malformed URL and replace it with a URL made out of
    // "http://badurl.com" so that the tests below pass

    urlClean("http://artima.com") should be (new URL("http://artima.com"))
    urlClean("http://javaposse.com") should be (new URL("http://javaposse.com"))
    urlClean("bad:url:malformed") should be (new URL("http://badurl.com"))
  }

  test ("Opposites matcher") {
    // convert the following method so that instead of returning the same string passed in, it returns
    // the opposite using the following heuristics:
    // North should return South
    // Hot should return Cold
    // Cool should return Square
    // anything else should return the same value with "Not " in front of it - e.g. A Lot should return Not A Lot
    // Use pattern matching

    def oppositeOf(item: String) =
      item match {
        case "North" => "South"
        case "Hot" => "Cold"
        case "Cool" => "Square"
        case anythingElse => "Not " + anythingElse
      }

    oppositeOf("North") should be ("South")
    oppositeOf("Hot") should be ("Cold")
    oppositeOf("Cool") should be ("Square")
    oppositeOf("Hip") should be ("Not Hip")
    oppositeOf("Funny") should be ("Not Funny")
  }
}
