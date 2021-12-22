
/* Copyright (C) 2010-2018 Escalate Software, LLC. All rights reserved. */

package koans.support

object BlankValues {
    class ReplaceWithCorrectException extends Exception

    val __ = "Should be filled in"
    class ___ extends ReplaceWithCorrectException {
        override def toString() = "___"
    }
}

