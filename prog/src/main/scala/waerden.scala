object waerden {
  def main(args: Array[String]) {
    val j = args(0).toInt
    val k = args(1).toInt
    val n = args(2).toInt
    for (d <- 1 to n; i <- 1 to n; if i+(j-1)*d <= n)
      println((i to i+(j-1)*d by d).mkString(" "))
    for (d <- 1 to n; i <- 1 to n; if i+(k-1)*d <= n)
      println((i to i+(k-1)*d by d).map("~" + _).mkString(" "))
  }
}
