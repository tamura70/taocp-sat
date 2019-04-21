import scala.collection.mutable.BitSet

class SolverC extends Solver {
  var MEM: Array[Int] = Array.empty
  var W: Array[Int] = Array.empty
  var R: Array[Int] = Array.empty
  var S: Array[Int] = Array.empty
  var VAL: Array[Int] = Array.empty
  var OVAL: Array[Int] = Array.empty
  var TLOC: Array[Int] = Array.empty
  var HLOC: Array[Int] = Array.empty
  var ACT: Array[Double] = Array.empty
  var HEAP: Array[Int] = Array.empty // 0 until nVars
  def load(cnf: Seq[Seq[Int]], name: Seq[String] = Seq.empty) {
    this.name = name.toArray
    nVars = cnf.map(_.max).max
    nClauses = cnf.size
    nCells = cnf.map(_.size).sum
    // START = new Array(nClauses+1)
    // LINK =  new Array(nClauses+1)
    W = new Array(2*nVars+2)
    // NEXT = new Array(nVars+1)
    // L = new Array(nCells)
    // X = new Array(nVars+1)
    // M = new Array(nVars+1)
    // H = new Array(nVars+1)
    bytes += 8 * (nVars+1)
    bytes += 8 * (nClauses+1)
    bytes += 16 * (nVars+1)
    bytes += 4 * nCells
    bytes += 8 * (nVars+1)
    bytes += 1 * (nVars+1)
  }
  def printDebug {
    // data
    // clauses
    // watches
  }
  def infoState(d: Int) {
    if (delta > 0 && mems >= thresh) {
      /*
      thresh += delta
      printErr(s" after $mems mems:")
      printlnErr((1 to d).map(M(_)).mkString(""))
      */
    }
  }
  def infoTrying(d: Int, nextmove: Int, v: Int) {
  if ((verbose & show_choices) > 0 && d <= show_choices_max) {
      /*
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
      */
    }
  }
  def infoReduced(c: Int, lit: Int) {
    // if ((verbose & show_details) > 0)
      // printlnErr(s"(Clause $c reduced to ${lit2name(lit)})")
  }
  def infoWatching(c: Int, lit: Int) {
    // if ((verbose & show_details) > 0)
      // printlnErr(s"(Clause $c now watches ${lit2name(lit)})")
  }
  def infoData(d: Int, h: Int, t: Int) {
    if (debug > 0) {
      /*
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
      */
    }
  }

  def C1 {
    val p: Seq[Int] = 0 to nVars // random permutation
    for (k <- 1 to nVars) {
      // VAL(k) = -1; OVAL(k) = -1; TLOC(k) = -1
      // ACT(k) = 0; S(k) = 0; R(2*k) = None; R(2*k+1) = None
      // HLOC(k) = p(k) - 1; HEAP(p(k) - 1) = k
      // watch list
      // if queue constains conflict literals return false
    }
  }

  def solve: Int = {
    return 0
  }
}
object SolverC extends SolverC {
  def main(args: Array[String]) = _main(args)
}
