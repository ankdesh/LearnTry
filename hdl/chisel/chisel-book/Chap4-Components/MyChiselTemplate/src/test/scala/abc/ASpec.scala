// See README.md for license details.

package abc

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
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
class ATest extends AnyFlatSpec with ChiselScalatestTester {

  "ATest" should "pass" in {
    test(new CompA()) { dut =>
      dut.io.a.poke(1.U)
      dut.io.b.poke(2.U)
      dut.clock.step()
      
      // println("Out = " + dut.io.y.peek().toString())

      dut.io.x.expect(2.U)
      dut.io.y.expect(1.U)
    }
  }
}
