import scala.annotation.tailrec

object FactSeq {

  def factSeq(n: Int): List[Long] = {
    factSeqInner(n, List(1L), 2)
  }

  @tailrec
  private def factSeqInner(n: Int, acc: List[Long], ct: Int): List[Long] = {
    if (ct > n) acc else
      factSeqInner(n, ct * acc.head :: acc, ct + 1)
  }
}

FactSeq.factSeq(8)


object FactSeqNested {

  def factSeq(n: Int): List[Long] = {
    @tailrec
    def factSeqInner(n: Int, acc: List[Long], ct: Int): List[Long] = {
      if (ct > n) acc else
        factSeqInner(n, ct * acc.head :: acc, ct + 1)
    }

    factSeqInner(n, List(1L), 2)
  }
}

FactSeqNested.factSeq(8)


object FactSeqScoped {

  def factSeq(n: Int): List[Long] = {
    @tailrec
    def factSeqInner(acc: List[Long], ct: Int): List[Long] = {
      if (ct > n) acc else
        factSeqInner(ct * acc.head :: acc, ct + 1)
    }

    factSeqInner(List(1L), 2)
  }
}

FactSeqScoped.factSeq(8)
