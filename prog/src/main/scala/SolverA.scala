import scala.collection.mutable.BitSet

class SolverA extends Solver {
  var START: Array[Int] = Array.empty
  var SIZE: Array[Int] = Array.empty
  var L: Array[Int] = Array.empty
  var F: Array[Int] = Array.empty
  var B: Array[Int] = Array.empty
  var C: Array[Int] = Array.empty
  var M: Array[Int] = Array.empty
  def load(cnf: Seq[Seq[Int]], name: Seq[String] = Seq.empty) {
    this.name = name.toArray
    nVars = cnf.map(_.max).max
    nClauses = cnf.size
    nCells = cnf.map(_.size).sum
    START = new Array(nClauses+1)
    SIZE =  new Array(nClauses+1)
    val size = 2*nVars + 2 + nCells
    L = new Array(size)
    F = new Array(size)
    B = new Array(size)
    C = new Array(size)
    bytes += 8 * (nVars+1)
    bytes += 8 * (nClauses+1)
    bytes += 16 * size
    M = new Array(nVars+1)
    for (lit <- 2 to 2*nVars+1) {
      F(lit) = lit; B(lit) = lit; C(lit) = 0
      imems += 3
    }
    var p = 2*nVars + 2
    for (j <- nClauses to 1 by -1) {
      val clause = cnf(j-1).sortWith((a,b) => math.abs(a) >= math.abs(b))
      if (clause.isEmpty)
        printlnErr(s"Warning: Clause $j is empty")
      if (clause.sliding(2).exists(x => x(0) == x(1)))
        printlnErr(s"Warning: Clause $j has duplicating literals")
      if (clause.sliding(2).exists(x => x(0) == -x(1)))
        printlnErr(s"Warning: Clause $j is a tautology")
      START(j) = p; SIZE(j) = clause.size
      imems += 2
      for (lit0 <- clause; lit = dimacs2lit(lit0)) {
        C(p) = j; L(p) = lit
        F(p) = F(lit); B(F(lit)) = p; F(lit) = p; B(p) = lit
        C(lit) += 1
        p += 1
        imems += 9
      }
    }
  }
  def printDebug {
    // data
    def toStr(xs: Seq[Int]) = xs.map("%2d".format(_)).mkString(" ")
    printlnErr(s"nVars = $nVars")
    printlnErr(s"nClauses = $nClauses")
    printlnErr(s"nCells = $nCells")
    printlnErr(s"START(1..$nClauses) = " + toStr(START.tail))
    printlnErr(s" SIZE(1..$nClauses) = " + toStr(SIZE.tail))
    printlnErr("L = " + toStr(L))
    printlnErr("F = " + toStr(F))
    printlnErr("B = " + toStr(B))
    printlnErr("C = " + toStr(C))
    // clauses
    for (i <- 1 to nClauses) {
      val lits = for (j <- START(i) until START(i)+SIZE(i)) yield lit2name(L(j))
      printlnErr(s"Clause $i = " + lits.mkString(" "))
    }
    // watches
    for (lit <- 2 to 2*nVars+1) {
      var list: Seq[String] = Seq.empty
      var p = F(lit)
      while (p >= 2*nVars + 2) {
        list = list :+ C(p).toString; p = F(p)
      }
      printlnErr(s"Watch ${lit2name(lit)} = " + list.mkString(" "))
    }
    printlnErr
  }
  def infoUnsatisfied(c: Int) {
    if ((verbose & show_details) > 0)
      printlnErr(s"(Clause $c now unsatisfied)")
  }
  def infoTrying(d: Int, a: Int) {
    if ((verbose & show_choices) > 0 && d <= show_choices_max) {
      val sign = if ((M(d)&1) == 0) "" else "~"
      printErr(s"Level $d, trying $sign$d")
      if ((verbose & show_details) > 0)
        printErr(s" (${C(2*d)}:${C(2*d+1)}, $a active, $mems mems)")
      printlnErr
    }
    if (delta > 0 && mems >= thresh) {
      thresh += delta
      printErr(s" after $mems mems:")
      printlnErr((1 to d).map(M(_)).mkString(""))
    }
  }
  def infoTryingAgain(d: Int, a: Int) {
    if ((verbose & show_choices) > 0 && d <= show_choices_max) {
      printErr(s"Level $d, trying again")
      if ((verbose & show_details) > 0) {
        printErr(s" ($a active, $mems mems)")
      }
      printlnErr
    }
  }

  def A3(l: Int): Boolean = {
    var conflict = false
    var p = F(l^1)
    mems += 1
    while (! conflict && p >= 2*nVars + 2) {
      var j = C(p)
      var i = SIZE(j)
      mems += 2
      if (i > 1) {
        SIZE(j) = i - 1; p = F(p)
        mems += 2
      } else {
        conflict = true
        infoUnsatisfied(j)
        p = B(p)
        mems += 1
        while (p >= 2*nVars + 2) {
          j = C(p); i = SIZE(j); SIZE(j) = i + 1
          p = B(p)
          mems += 4
        }
      }
    }
    conflict
  }
  def A4(l: Int) {
    var p = F(l)
    mems += 1
    while (p >= 2*nVars + 2) {
      val j = C(p)
      val i = START(j)
      p = F(p)
      mems += 3
      for (s <- i until i + SIZE(j) - 1) {
        val q = F(s)
        val r = B(s)
        B(q) = r; F(r) = q
        C(L(s)) -= 1
        mems += 6
      }
    }
  }
  def A7(l: Int) {
    var p = B(l)
    mems += 1
    while (p >= 2*nVars + 2) {
      val j = C(p)
      val i = START(j)
      p = B(p)
      mems += 3
      for (s <- i until i + SIZE(j) - 1) {
        val q = F(s)
        val r = B(s)
        B(q) = s; F(r) = s
        C(L(s)) += 1
        mems += 6
      }
    }
  }
  def A8(l: Int) {
    var p = F(l^1)
    mems += 1
    while (p >= 2*nVars + 2) {
      val j = C(p)
      val i = SIZE(j)
      SIZE(j) = i + 1
      p = F(p)
      mems += 4
    }
  }

  def solve: Int = {
    // A1
    var a = nClauses
    var d = 1
    while (true) {
      // A2
      var l = 2*d
      if (C(l) <= C(l+1)) l += 1
      M(d) = (l&1)
      if (C(l^1) == 0)
        M(d) += 4
      else
        nodes += 1
      mems += 3
      infoTrying(d, a)
      if (mems > timeout) {
        printlnErr("TIMEOUT!")
        return -1
      }
      if (C(l) == a) {
        model = new BitSet
        for (i <- 1 to nVars)
          model(i) = ((M(i)&1) == 0)
        return 1
      }
      // A3
      while (A3(l)) {
        // A5
        while (M(d) >= 2) {
          mems += 1
          // A6
          if (d == 1) {
            return 0
          }
          d -= 1; l = 2*d + (M(d)&1)
          mems += 1
          // A7
          a += C(l)
          mems += 1
          A7(l)
          // A8
          A8(l)
        }
        M(d) = 3 - M(d); l = 2*d + (M(d)&1)
        mems += 2
        infoTryingAgain(d, a)
      }
      // A4
      A4(l); a -= C(l); d += 1
      mems += 1
    }
    return 0
  }
}
object SolverA extends SolverA {
  def main(args: Array[String]) = _main(args)
}


