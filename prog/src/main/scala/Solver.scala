import scala.collection.mutable.BitSet
import scala.io.Source

abstract class Solver {
  final val show_basics = 1
  final val show_choices = 2
  final val show_details = 4
  var random_seed = 0
  var verbose = show_basics
  var show_choices_max = 1000000
  var imems = 0L
  var mems = 0L
  var bytes = 0L
  var nodes = 0L
  var thresh = 0L
  var delta = 0L
  var timeout = 0x1fffffffffffffffL
  var debug = 0

  var nVars = 0
  var nClauses = 0
  var nCells = 0
  var name: Array[String] = Array.empty

  var model: BitSet = _

  def printErr(s: String) = Console.err.print(s)
  def printlnErr(s: String) = Console.err.println(s)
  def printlnErr = Console.err.println

  def var2name(i: Int) =
    if (i < name.size) name(i) else i.toString
  def lit2name(lit: Int) = {
    val s = var2name(lit >> 1)
    if ((lit&1) == 0) s else s"~$s"
  }
  def dimacs2lit(x: Int) = if (x < 0) -2*x+1 else 2*x
  def int(c: Boolean) = if (c) 1 else 0
  def load(cnf: Seq[Seq[Int]], name: Seq[String] = Seq.empty): Unit
  def load(source: Source) {
    import scala.collection.mutable.Map
    var cnf: Seq[Seq[Int]] = Seq.empty
    val map: Map[String,Int] = Map.empty
    val re = "~(.*)".r
    var c = 0
    for {
      line0 <- source.getLines
      line = line0.replaceAll("\\s+", " ").trim
      if line != ""
      if ! line.startsWith("~ ")
    } {
      val clause: Seq[Int] = line.split(" ").map {
        case re(s) if map.contains(s) =>
          -map(s)
        case re(s) => {
          c +=1; map += s -> c; -c
        }
        case s if map.contains(s) =>
          map(s)
        case s => {
          c +=1; map += s -> c; c
        }
      }
      cnf = cnf :+ clause
    }
    source.close
    val xmap = map.map(_.swap)
    val name = (0 to c).map(xmap.getOrElse(_, ""))
    load(cnf, name)
  }
  def printDebug: Unit
  def printModel {
    for (i <- 1 to nVars)
      print((if (model(i)) " " else " ~") + var2name(i))
    println
  }
  def solve: Int
  def run {
    solve match {
      case 1 => {
        printlnErr("!SAT!")
        printModel
      }
      case 0 => {
        println("~")
        printlnErr("UNSAT")
      }
      case _ => {
      }
    }
  }

  def parseOptions(args: Seq[String]): Seq[String] = {
    var rest: Seq[String] = Seq.empty
    for (arg <- args) {
      if (arg.matches("""v\d+""")) {
        verbose = arg.substring(1).toInt
      } else if (arg.matches("""c\d+""")) {
        show_choices_max = arg.substring(1).toInt
      } else if (arg.matches("""s\d+""")) {
        random_seed = arg.substring(1).toInt
      } else if (arg.matches("""d\d+""")) {
        delta = arg.substring(1).toLong; thresh = delta
      } else if (arg.matches("""T\d+""")) {
        timeout = arg.substring(1).toLong
      } else if (arg.matches("""D\d+""")) {
        debug = arg.substring(1).toInt
      } else {
        rest = rest :+ arg
      }
    }
    rest
  }
  def _main(args: Array[String]) {
    parseOptions(args) match {
      case Seq() => {
      }
      case _ => {
        printlnErr(s"scala $toString [v<n>] [c<n>] [s<n>] [d<n>] [T<n>] [D<n>] < foo.sat")
        sys.exit(-1)
      }
    }
    load(Source.stdin)
    if (debug >= 1) {
      printDebug
    }
    if ((verbose & show_basics) > 0) {
      printlnErr(s"($nVars variables, $nClauses clauses, $nCells literals successfully read)")
    }
    run
    if ((verbose & show_basics) > 0) {
      printlnErr(s"Altogether $imems+$mems mems, $bytes bytes, $nodes nodes.")
    }
  }
}
