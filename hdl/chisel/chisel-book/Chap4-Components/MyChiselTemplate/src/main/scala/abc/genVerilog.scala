package abc

import chisel3._

object PrintVerilog extends App {
    val s = getVerilogString(new CompC()) 
    println(s)
}