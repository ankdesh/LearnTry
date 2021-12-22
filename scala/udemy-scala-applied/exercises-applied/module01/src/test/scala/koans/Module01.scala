
/* Copyright (C) 2010-2018 Escalate Software, LLC. All rights reserved. */

package koans
import org.scalatest.Matchers
import support.KoanSuite
import org.scalatest.SeveredStackTraces

class Module01 extends KoanSuite with Matchers with SeveredStackTraces {

  test ("Something works") {
    1 should be (1)
  }
}
