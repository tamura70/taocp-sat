import scala.io.Source
import utils.{neg,atmostR_sinz,atmostR_bb}

object life {
  def load(source: Source): Seq[String] =
    source.mkString.split("\n")
  def pattern(p: Seq[String], t: String): Unit = {
    for (x <- 1 to p.size; y <- 1 to p(x-1).size; c = p(x-1)(y-1)) {
      val lit = s"$x$t$y"
      if (c == '*') println(lit)
      else if (c == '.') println(neg(lit))
    }
  }
  def threshold_sinz(m: Int, n: Int, r: Int, ts: Seq[String]): Unit = {
    for (t <- ts) {
      val xs = for (i <- 1 to m; j <- 1 to n) yield s"$i$t$j"
      atmostR_sinz(xs, r)
    }
  }
  def threshold_bb(m: Int, n: Int, r: Int, ts: Seq[String]): Unit = {
    for (t <- ts) {
      val xs = for (i <- 1 to m; j <- 1 to n) yield s"$i$t$j"
      atmostR_bb(xs, r)
    }
  }
  def main(args: Array[String]): Unit = {
    args(0) match {
      case "pattern" =>
        pattern(load(Source.stdin), args(1))
      case "threshold_sinz" =>
        threshold_sinz(args(1).toInt, args(2).toInt, args(3).toInt, args.drop(4))
      case "threshold_bb" =>
        threshold_bb(args(1).toInt, args(2).toInt, args(3).toInt, args.drop(4))
    }
  }
}
