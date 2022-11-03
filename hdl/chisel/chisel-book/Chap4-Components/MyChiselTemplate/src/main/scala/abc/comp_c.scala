package abc
import chisel3._


class CompC extends Module{
  val io = IO(new Bundle{
              val a = Input (UInt(8.W))
              val b = Input (UInt(8.W))
              val y = Output (UInt(8.W))
              })
    val compA = Module(new CompA())
    val compB = Module(new CompB())

    compA.io.a := io.a 
    compA.io.b := io.b 
    
    compB.io.a := compA.io.x
    compB.io.b := compA.io.y
    
    io.y := compB.io.y
}

