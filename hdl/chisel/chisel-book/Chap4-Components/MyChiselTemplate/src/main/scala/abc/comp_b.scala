package abc

import chisel3._


class CompB extends Module{
  val io = IO(new Bundle{
              val a = Input (UInt(8.W))
              val b = Input (UInt(8.W))
              val y = Output (UInt(8.W))
              })

        io.y := io.b + io.a
}

