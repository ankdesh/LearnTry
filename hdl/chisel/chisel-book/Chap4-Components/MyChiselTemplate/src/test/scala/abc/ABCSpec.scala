// See README.md for license details.

package abc

import chisel3._
import chiseltest._
import org.scalatest.freespec.AnyFreeSpec
import chisel3.experimental.BundleLiterals._
import abc._

/**
  * This is a trivial example of how to run this Specification
  * From within sbt use:
  * {{{
  * testOnly gcd.GcdDecoupledTester
  * }}}
  * From a terminal shell use:
  * {{{
  * sbt 'testOnly gcd.GcdDecoupledTester'
  * }}}
  */
class ABC extends AnyFreeSpec with ChiselScalatestTester {

  "ABC should learn to behave" in {
    test(new CompC()) { dut =>
      dut.io.a.poke(1.U)
      dut.io.b.poke(2.U)
      dut.clock.step()
      
      println("Out = " + dut.io.y.peek().toString())
    }
  }
}
