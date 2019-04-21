import scala.collection.mutable.BitSet

class SolverB extends Solver {
  var START: Array[Int] = Array.empty
  var LINK: Array[Int] = Array.empty
  var W: Array[Int] = Array.empty
  var L: Array[Int] = Array.empty
  var M: Array[Int] = Array.empty
  def load(cnf: Seq[Seq[Int]], name: Seq[String] = Seq.empty) {
    this.name = name.toArray
    nVars = cnf.map(_.max).max
    nClauses = cnf.size
    nCells = cnf.map(_.size).sum
    START = new Array(nClauses+1)
    LINK =  new Array(nClauses+1)
    W = new Array(2*nVars+2)
    L = new Array(nCells)
    bytes += 8 * (nVars+1)
    bytes += 8 * (2*nVars + 2 + nClauses)
    bytes += 4 * nCells
    M = new Array(nVars+1)
    var p = 0
    for (j <- nClauses to 1 by -1) {
      val clause = cnf(j-1).sortWith((a,b) => math.abs(a) >= math.abs(b))
      if (clause.isEmpty)
        printlnErr(s"Warning: Clause $j is empty")
      if (clause.sliding(2).exists(x => x(0) == x(1)))
        printlnErr(s"Warning: Clause $j has duplicating literals")
      if (clause.sliding(2).exists(x => x(0) == -x(1)))
        printlnErr(s"Warning: Clause $j is a tautology")
      START(j) = p
      imems += 1
      for (lit0 <- cnf(j-1).reverse; lit = dimacs2lit(lit0)) {
        L(p) = lit
        p += 1
        imems += 1
      }
      val lit = L(START(j))
      LINK(j) = W(lit); W(lit) = j
      imems += 4
    }
    START(0) = p
    imems += 1
  }
  def printDebug {
    // data
    def toStr(xs: Seq[Int]) = xs.map("%2d".format(_)).mkString(" ")
    printlnErr(s"nVars = $nVars")
    printlnErr(s"nClauses = $nClauses")
    printlnErr(s"nCells = $nCells")
    printlnErr(s"START(0..$nClauses) = " + toStr(START))
    printlnErr(s" LINK(0..$nClauses) = " + toStr(LINK))
    printlnErr("L = " + toStr(L))
    printlnErr("W = " + toStr(W))
    // clauses
    for (i <- 1 to nClauses) {
      val lits = for (j <- START(i) until START(i-1)) yield lit2name(L(j))
      printlnErr(s"Clause $i = " + lits.mkString(" "))
    }
    // watches
    for (lit <- 2 to 2*nVars+1) {
      var list: Seq[String] = Seq.empty
      var i = W(lit)
      while (i > 0) {
        list = list :+ i.toString; i = LINK(i)
      }
      printlnErr(s"Watch ${lit2name(lit)} = " + list.mkString(" "))
    }
    printlnErr
  }
  def infoUnsatisfied(c: Int) {
    if ((verbose & show_details) > 0)
      printlnErr(s"(Clause $c now unsatisfied)")
  }
  def infoTrying(d: Int) {
    if ((verbose & show_choices) > 0 && d <= show_choices_max) {
      val sign = if ((M(d)&1) == 0) "" else "~"
      printErr(s"Level $d, trying $sign$d")
      if ((verbose & show_details) > 0)
        printErr(s" ($mems mems)")
      printlnErr
    }
    if (delta > 0 && mems >= thresh) {
      thresh += delta
      printErr(s" after $mems mems:")
      printlnErr((1 to d).map(M(_)).mkString(""))
    }
  }
  def infoTryingAgain(d: Int) {
    if ((verbose & show_choices) > 0 && d <= show_choices_max) {
      printErr(s"Level $d, trying again")
      if ((verbose & show_details) > 0) {
        printErr(s" ($mems mems)")
      }
      printlnErr
    }
  }
  def infoContradiction(c: Int) {
    if ((verbose & show_details) > 0)
      printlnErr(s"(Clause $c contradicted)")
  }
  def infoWatching(c: Int, lit: Int) {
    if ((verbose & show_details) > 0)
      printlnErr(s"(Clause $c now watches ${lit2name(lit)})")
  }

  def B3(l: Int, d: Int): Boolean = {
    var j = W(l^1)
    mems += 1
    while (j != 0) {
      val i = START(j)
      val i1 = START(j-1)
      val j1 = LINK(j)
      mems += 2
      var k = i + 1
      var break = false
      while (! break && k < i1) {
        val l1 = L(k); val l2 = l1>>1
        mems += 1
        if (l2 <= d) mems += 1
        if (l2 > d || ((l1 + M(l2))&1) == 0) {
          infoWatching(j, l1)
          L(i) = l1; L(k) = l^1; LINK(j) = W(l1); W(l1) = j; j = j1
          mems += 5
          break = true
        } else {
          k += 1
        }
      }
      if (k == i1) {
        infoContradiction(j)
        W(l^1) = j
        mems += 1
        return true
      }
    }
    return false
  }
  def solve: Int = {
    // B1
    var d = 1
    while (true) {
      // B2
      if (d > nVars) {
        model = new BitSet
        for (i <- 1 to nVars)
          model(i) = ((M(i)&1) == 0)
        return 1
      }
      M(d) = int(W(2*d) == 0 || W(2*d+1) != 0)
      var l = 2*d + M(d)
      mems += 2
      nodes += 1
      infoTrying(d)
      if (mems > timeout) {
        printlnErr("TIMEOUT!")
        return -1
      }
      // B3
      while (B3(l, d)) {
        // B5
        while (M(d) >= 2) {
          mems += 1
          // B6
          if (d == 1) {
            return 0
          }
          d -= 1
        }
        M(d) = 3 - M(d); l = 2*d + (M(d)&1)
        mems += 2
        infoTryingAgain(d)
      }
      // B4
      W(l^1) = 0; d += 1
      mems += 1
    }
    return 0
  }
}
object SolverB extends SolverB {
  def main(args: Array[String]) = _main(args)
}
