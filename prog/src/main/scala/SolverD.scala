import scala.collection.mutable.BitSet

class SolverD extends Solver {
  var START: Array[Int] = Array.empty
  var LINK: Array[Int] = Array.empty
  var W: Array[Int] = Array.empty
  var NEXT: Array[Int] = Array.empty
  var L: Array[Int] = Array.empty
  var X: Array[Int] = Array.empty
  var M: Array[Int] = Array.empty
  var H: Array[Int] = Array.empty
  def load(cnf: Seq[Seq[Int]], name: Seq[String] = Seq.empty) {
    this.name = name.toArray
    nVars = cnf.map(_.max).max
    nClauses = cnf.size
    nCells = cnf.map(_.size).sum
    START = new Array(nClauses+1)
    LINK =  new Array(nClauses+1)
    W = new Array(2*nVars+2)
    NEXT = new Array(nVars+1)
    L = new Array(nCells)
    X = new Array(nVars+1)
    M = new Array(nVars+1)
    H = new Array(nVars+1)
    bytes += 8 * (nVars+1)
    bytes += 8 * (nClauses+1)
    bytes += 16 * (nVars+1)
    bytes += 4 * nCells
    bytes += 8 * (nVars+1)
    bytes += 1 * (nVars+1)
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
    printlnErr("NEXT = " + toStr(NEXT))
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
  def infoState(d: Int) {
    if (delta > 0 && mems >= thresh) {
      thresh += delta
      printErr(s" after $mems mems:")
      printlnErr((1 to d).map(M(_)).mkString(""))
    }
  }
  def infoTrying(d: Int, nextmove: Int, v: Int) {
    if ((verbose & show_choices) > 0 && d <= show_choices_max) {
      printErr(s"Level $d, ")
      nextmove match {
        case 0 => printErr(s"trying ${var2name(v)}")
        case 1 => printErr(s"trying ~${var2name(v)}")
        case 2 => printErr(s"retrying ${var2name(v)}")
        case 3 => printErr(s"retrying ~${var2name(v)}")
        case 4 => printErr(s"forcing ${var2name(v)}")
        case 5 => printErr(s"forcing ~${var2name(v)}")
      }
      printlnErr(s", $mems mems")
    }
  }
  def infoReduced(c: Int, lit: Int) {
    if ((verbose & show_details) > 0)
      printlnErr(s"(Clause $c reduced to ${lit2name(lit)})")
  }
  def infoWatching(c: Int, lit: Int) {
    if ((verbose & show_details) > 0)
      printlnErr(s"(Clause $c now watches ${lit2name(lit)})")
  }
  def infoData(d: Int, h: Int, t: Int) {
    if (debug > 0) {
      printErr("Active ring =")
      if (t != 0) {
        var k = h
        do {
          printErr(s" $k")
          k = NEXT(k)
        } while (k != h)
      }
      printlnErr
      val s = (1 to nVars).map(X(_)).map {
        case -1 => "-"
        case x => x.toString
      }
      printlnErr(s.mkString("Assignments = ", " ", ""))
    }
  }

  def D3a(lit: Int): Int = {
    var j = W(lit); mems += 1
    while (j != 0) {
      var p = START(j); mems += 2
      do {
        p += 1
        if (p == START(j-1)) {
          infoReduced(j, lit)
          return 1
        }
        mems += 2
      } while (X(L(p)>>1) == (L(p)&1))
      j = LINK(j); mems += 1
    }
    return 0
  }
  def solve: Int = {
    // D1
    M(0) = 0; mems += 1
    var d = 0; var h = 0; var t = 0
    for (k <- nVars to 1 by -1) {
      X(k) = -1
      mems += 1
      if (W(2*k) != 0 || W(2*k+1) != 0) {
        NEXT(k) = h; h = k; mems += 1
        if (t == 0)
          t = k
      }
    }
    if (t != 0) {
      NEXT(t) = h; mems += 1
    }
    while (true) {
      // D2
      infoData(d, h, t)
      infoState(d)
      if (mems > timeout) {
        printlnErr("TIMEOUT!")
        return -1
      }
      if (t == 0) {
        model = new BitSet
        for (i <- 1 to nVars)
          model(i) = math.max(0, X(i)) == 1
        return 1
      }
      var k = t
      // D3
      var break = 0
      while (break == 0) {
        h = NEXT(k); mems += 1
        val f = D3a(2*h) + 2*D3a(2*h+1)
        if (f == 3) {
          break = -1 // backtrack
        } else if (f == 1 || f == 2) {
          M(d+1) = f + 3; t = k
          break = 1 // propagate
        } else if (h == t) {
          break = 2 // branch
        } else {
          k = h
        }
      }
      if (break > 0) {
        if (break == 2) {
          // D4
          nodes += 1
          h = NEXT(t)
          M(d+1) = int(W(2*h) == 0 || W(2*h+1) != 0)
          mems += 1
        }
        // D5
        d += 1; k = h; H(d) = k; mems += 1
        if (t == k) {
          t = 0
        } else {
          h = NEXT(k); NEXT(t) = h; mems += 2
        }
      } else {
        // D7
        t = k; mems += 1
        while (M(d) >= 2) {
          k = H(d); X(k) = -1; mems += 3
          if (W(2*k) != 0 || W(2*k+1) != 0) {
            NEXT(k) = h; h = k; NEXT(t) = h; mems += 2
          }
          d -= 1
        }
        // D8
        if (d == 0)
          return 0
        M(d) = 3 - M(d); k = H(d); mems += 2
      }
      // D6
      infoTrying(d, M(d), k)
      val b = (M(d)+1)&1; X(k) = b
      val l = 2*k+b; var j = W(l); W(l) = 0; mems += 3
      while (j != 0) {
        val j1 = LINK(j); val i = START(j)
        var p = i + 1
        mems += 3
        while (X(L(p)>>1) == (L(p)&1)) {
          p += 1; mems += 2
        }
        val l1 = L(p); L(p) = l; L(i) = l1; mems += 2
        infoWatching(j, l1)
        p = W(l1); var q = W(l1^1); mems += 1
        if (p == 0 && q == 0 && X(l1>>1) < 0) {
          if (t == 0) {
            h = l1>>1; t = h; NEXT(t) = h; mems += 1
          } else {
            NEXT(l1>>1) = h; h = l1>>1; NEXT(t) = h; mems += 2
          }
        }
        LINK(j) = p; W(l1) = j; mems += 2
        j = j1
        mems += 2 // to match with sat10
      }
    }
    return 0
  }
}
object SolverD extends SolverD {
  def main(args: Array[String]) = _main(args)
}
