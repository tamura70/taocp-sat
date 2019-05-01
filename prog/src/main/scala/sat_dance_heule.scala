import utils.{exact1_heule}

object sat_dance_heule {
  def encodeExactCover(cols: Seq[String], rows: Seq[Set[String]]): Unit = {
    for (col <- cols) {
      val is = (1 to rows.size).filter(i => rows(i-1).contains(col))
      exact1_heule(is.map(_.toString))
    }
  }
  def main(args: Array[String]): Unit = {
    val source = scala.io.Source.stdin
    val lines = source.getLines.toSeq
    val cols = lines.head.split("\\s+")
    val rows = lines.tail.map(_.split("\\s+").toSet)
    encodeExactCover(cols, rows)
  }
}
