object langford {
  def apply(n: Int): Unit = {
    val cols = (1 to n).map(i => s"d$i") ++
               (1 to 2*n).map(j => s"s$j")
    println(cols.mkString(" "))
    for {
      i <- 1 to n; j <- 1 to 2*n
      k = i+j+1; if k <= 2*n
      if i < n || 2*j <= n
    } println(s"d$i s$j s$k")
  }

  def main(args: Array[String]): Unit = {
    val n = args(0).toInt
    this(n)
  }
}
