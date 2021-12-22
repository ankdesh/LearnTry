
/* Copyright (C) 2010-2018 Escalate Software, LLC. All rights reserved. */

package koans
import org.scalatest.Matchers
import support.BlankValues._
import support.KoanSuite
import org.scalatest.SeveredStackTraces

// in the following tests, __ should be filled in with the correct answer for the
// value to match. Think of __ as a blank value to be replaced, and the tests won't
// pass until you do.

class Module02Solutions extends KoanSuite with Matchers with SeveredStackTraces {

  test ("Parameterize arrays with type") {
    val greetStrings = new Array[String](3)
    greetStrings(0) = "Hello"
    greetStrings(1) = ", "
    greetStrings(2) = "World"

    // what happens if you replace the above line with:
    // greetStrings(2) = 2

    // join the strings together
    val concat = greetStrings(0) + greetStrings(1) + greetStrings(2)

    // and what should this equal?
    concat should be ("Hello, World")
  }

  test ("Array creation") {
    // Calling Array() directly invokes the apply method - the following two statements are equivalent
    val numNames = Array("zero", "one", "two")
    val numNames2 = Array.apply("zero", "one", "two")

    numNames.length should be (3)
    numNames2.length should be (3)

    (numNames == numNames2) should be (false)    
    // Why? Because the underlying implementation for Array is Java and uses Java's .equals method
    // for arrays - if you want to test array equality in scala, you can use
    // numNames.deep == numNames2.deep which will be true.
  }

  test ("List immutability") {
    val oneTwo = List(1,2)
    val threeFour = List(3,4)
    
    val oneTwoThreeFour = oneTwo ::: threeFour
    
    oneTwo should be (List(1, 2))
    threeFour should be (List(3, 4))
    oneTwoThreeFour should be (List(1, 2, 3, 4))
  }

  test ("List cons") {
    val twoThree = List(2,3)
    val newList = 1 :: twoThree
    val newList2 = twoThree.::(1)

    newList should be (List(1, 2, 3))
    newList2 should be (List(1, 2, 3))
  }

  test ("Create a list and convert to Array") {
    // fill in the method below to concatenate the two lists and then convert them to an array
    // so that it satisfies the tests below
    //

    def concatListsToArray(l1 : List[Int], l2 : List[Int]) : Array[Int] = {
      // replace this with the correct implementation
      (l1 ++ l2).toArray  // or you could use :::
    }

    val oneTwo = List(1,2)
    val threeFour = List(3,4)

    concatListsToArray(oneTwo, threeFour) should equal (Array(1,2,3,4))
  }

  test ("Take two arrays, and concatenate them in a list") {
    def concatArraysToList(a1 : Array[Int], a2 : Array[Int]) : List[Int] = {
      // replace this with the correct implementation
      (a1 ++ a2).toList
    }

    val oneTwo = Array(1,2)
    val threeFour = Array(3,4)

    concatArraysToList(oneTwo, threeFour) should equal (List(1,2,3,4))
  }

  test ("Exploring Tuples") {
    val t = (0, 'u', 8, 1, "too")

    t._1 should be (0)
    t._2 should be ('u')
    t._3 should be (8)
    t._4 should be (1)
    t._5 should be ("too")

    // Arity is the number of arguments
    t.productArity should be (5)

    // and you can iterate over the arguments too
    t.productIterator.next should be (0)
  }

  test ("Map a tuple to strings") {
    val t = (0, 'u', 8, 1, "too")

    // replace the following with the correct code to convert tuple t
    // to a list of strings
    val l = List(t._1.toString, t._2.toString, t._3.toString, t._4.toString, t._5.toString)  // better ways to do this
    // but we will cover those later.

    l should be (List("0", "u", "8", "1", "too"))
  }

  test ("Immutable set in var") {
    var getSet = Set("Ready", "Steady")

    // Add a line below to satisfy the test
    getSet += "Go!"

    getSet should be (Set("Ready", "Steady", "Go!"))
    
    // What happens if you make the var a val above? Why?
  }

  test ("Mutable set in a val") {
    var getSet = scala.collection.mutable.Set("Ready", "Steady")

    // Add a line below to satisfy the test
    getSet += "Go!"

    getSet should be (Set("Ready", "Steady", "Go!"))

    // what happens if you make the var a val above? Why? Is this a good idea?
  }

  test ("Immutable map in a var") {
    var mutMap = Map[Int, String]()

    mutMap += (1 -> "Uno")
    mutMap += (2 -> "Dos")
    mutMap += (3 -> "Tres")

    mutMap(2) should be ("Dos")

    mutMap += (2 -> "Two")

    mutMap(2) should be ("Two")

    // What happens if you uncomment the line below? Why?
    // mutMap += (2 -> 2)
    mutMap(2) should be ("Two")
  }

  test ("Mutable map in a val") {
    val mutMap = scala.collection.mutable.Map[Int, String]()

    mutMap += (1 -> "Uno")
    mutMap += (2 -> "Dos")
    mutMap += (3 -> "Tres")

    mutMap(2) should be ("Dos")

    mutMap(2) = "Two"

    mutMap(2) should be ("Two")

    mutMap += (2 -> "Deux")

    mutMap(2) should be ("Deux")

    // What happens if you uncomment the line below? Why?
    // mutMap += (2 -> 2)
    mutMap(2) should be ("Deux")
  }
}
