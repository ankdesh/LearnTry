
/* Copyright (C) 2010-2018 Escalate Software, LLC. All rights reserved. */

package koans.support

import org.scalatest.Reporter
import org.scalatest.Stopper
import org.scalatest.Distributor
import org.scalatest.Filter
import org.scalatest.Tracker
import org.scalatest.FunSuite
import org.scalatest.events.Event
import org.scalatest.events.TestSucceeded
import org.scalatest.Args
import scala.collection.mutable.ListBuffer
import org.scalatest.Status
import org.scalatest.CompositeStatus
import org.scalatest.SuiteMixin
import org.scalatest.Suite

trait StopOnFirstFailure extends SuiteMixin { this: Suite =>

  override def runTests(testName : Option[String], args: Args): Status = {

    import args._

    val stopRequested = stopper

    // If a testName is passed to run, just run that, else run the tests returned
    // by testNames.
    testName match {
      case Some(tn) => runTest(tn, args)
      case None =>
        val statusList = new ListBuffer[Status]()
        val tests = testNames.iterator
        var failed = false
        for (test <- tests) {
          if (failed == false) {
            val status = runTest(test, args)
            statusList += status
            failed = !status.succeeds()
          }
        }
        new CompositeStatus(Set.empty ++ statusList)
    }
  }
}

