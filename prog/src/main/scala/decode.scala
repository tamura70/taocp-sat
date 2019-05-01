import utils.{v}

object decode {
  def decodeOutput(result: String, vs: Seq[String]): Map[(String,Int),Boolean] = {
    val seq = for {
      lit <- result.split("\\s+")
      neg = lit.startsWith("~")
      x = if (neg) lit.substring(1) else lit
      v <- vs
      if x.startsWith(v)
      s = x.substring(v.size)
      if s.matches("\\d+")
    } yield (v,s.toInt) -> ! neg
    seq.toMap
  }
  def decodeDirect(map: Map[(String,Int),Boolean], vs: Seq[String]): Unit = {
    for (v <- vs) {
      val is = map.keys.filter(_._1 == v).map(_._2)
      if (is.isEmpty) {
        println(s"$v = unknown")
      } else {
        val values = is.filter(i => map((v,i))).toSeq.sorted
        println(values.mkString(s"$v = ", ",", ""))
      }
    }
  }
  def decodeLog(map: Map[(String,Int),Boolean], vs: Seq[String]): Unit = {
    for (v <- vs) {
      val is = map.keys.filter(_._1 == v).map(_._2)
      if (is.isEmpty) {
        println(s"$v = unknown")
      } else {
        val n0 = is.min
        val n1 = is.max
        val bs = for (i <- n1 to n0 by -1)
                 yield if (! map.contains((v,i))) "?"
                       else if (map((v,i))) "1"
                       else "0"
        val b = bs.mkString
        if (b.contains("?")) {
          println(s"$v($n1..$n0) = ${b}_2")
        } else {
          val d = BigInt(b, 2)
          println(s"$v($n1..$n0) = ${b}_2 = $d")
        }
      }
    }
  }
  def main(args: Array[String]): Unit = {
    val result = scala.io.Source.stdin.mkString.trim
    result match {
      case "" => println("ERROR")
      case "~" => println("UNSAT")
      case _ => {
        val vs = args.tail
        val map = decodeOutput(result, vs)
        args(0) match {
          case "direct" =>
            decodeDirect(map, vs)
          case "log" =>
            decodeLog(map, vs)
        }
      }
    }
  }
}
