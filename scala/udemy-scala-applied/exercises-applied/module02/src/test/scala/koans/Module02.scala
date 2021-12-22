
/* Copyright (C) 2010-2018 Escalate Software, LLC. All rights reserved. */

package koans
import org.scalatest.Matchers
import support.BlankValues._
import support.KoanSuite
import org.scalatest.SeveredStackTraces

// in the following tests, __ should be filled in with the correct answer for the
// value to match. Think of __ as a blank value to be replaced, and the tests won't
// pass until you do.

class Module02 extends KoanSuite with Matchers with SeveredStackTraces {

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
    concat should be (__)
  }

  test ("Array creation") {
    // Calling Array() directly invokes the apply method - the following two statements are equivalent
    val numNames = Array("zero", "one", "two")
    val numNames2 = Array.apply("zero", "one", "two")

    numNames.length should be (__)
    numNames2.length should be (__)

    (numNames == numNames2) should be (__)

    (numNames sameElements numNames2) should be (__)
  }

  test ("List immutability") {
    val oneTwo = List(1,2)
    val threeFour = List(3,4)
    
    val oneTwoThreeFour = oneTwo ::: threeFour
    
    oneTwo should be (__)
    threeFour should be (__)
    oneTwoThreeFour should be (__)
  }

  test ("List cons") {
    val twoThree = List(2,3)
    val newList = 1 :: twoThree
    val newList2 = twoThree.::(1)

    newList should be (__)
    newList2 should be (__)
  }

  test ("Create a list and convert to Array") {
    // fill in the method below to concatenate the two lists and then convert them to an array
    // so that it satisfies the tests below
    //

    def concatListsToArray(l1 : List[Int], l2 : List[Int]) : Array[Int] = {
      // replace this with the correct implementation
      Array(0)
    }

    val oneTwo = List(1,2)
    val threeFour = List(3,4)

    concatListsToArray(oneTwo, threeFour) should equal (Array(1,2,3,4))
  }

  test ("Take two arrays, and concatenate them in a list") {
    def concatArraysToList(a1 : Array[Int], a2 : Array[Int]) : List[Int] = {
      // replace this with the correct implementation
      List(0)
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
    t.productArity should be (__)

    // and you can iterate over the arguments too
    t.productIterator.next should be (__)
  }

  test ("Map a tuple to strings") {
    val t = (0, 'u', 8, 1, "too")

    // replace the following with the correct code to convert tuple t
    // to a list of strings
    val l = Nil

    l should be (List("0", "u", "8", "1", "too"))
  }

  test ("Immutable set in var") {
    var getSet = Set("Ready", "Steady")

    // Add a line below to satisfy the test

    getSet should be (Set("Ready", "Steady", "Go!"))
    
    // What happens if you make the var a val above? Why?
  }

  test ("Mutable set in a val") {
    var getSet = scala.collection.mutable.Set("Ready", "Steady")

    // Add a line below to satisfy the test

    getSet should be (Set("Ready", "Steady", "Go!"))

    // what happens if you make the var a val above? Why? Is this a good idea?
  }

  test ("Immutable map in a var") {
    var mutMap = Map[Int, String]()

    mutMap += (1 -> "Uno")
    mutMap += (2 -> "Dos")
    mutMap += (3 -> "Tres")

    mutMap(2) should be (__)

    mutMap += (2 -> "Two")

    mutMap(2) should be (__)

    // What happens if you uncomment the line below? Why?
    // mutMap += (2 -> 2)
    mutMap(2) should be (__)
  }

  test ("Mutable map in a val") {
    val mutMap = scala.collection.mutable.Map[Int, String]()

    mutMap += (1 -> "Uno")
    mutMap += (2 -> "Dos")
    mutMap += (3 -> "Tres")

    mutMap(2) should be (__)

    mutMap(2) = "Two"

    mutMap(2) should be (__)

    mutMap += (2 -> "Deux")

    mutMap(2) should be (__)

    // What happens if you uncomment the line below? Why?
    // mutMap += (2 -> 2)
    mutMap(2) should be (__)
  }
}
