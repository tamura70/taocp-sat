object triples {
  def pythagorean(n: Int): Unit = {
    for {
      a <- 1 to (n/math.sqrt(2)).toInt + 1
      b <- a+1 to math.sqrt(n*n - a*a).toInt + 1
      c = math.sqrt(a*a + b*b + 0.5).toInt
      if a*a + b*b == c*c
      if c <= n
    } {
      println(s"$a $b $c")
      println(s"~$a ~$b ~$c")
    }
  }
  def main(args: Array[String]): Unit = {
    args(0) match {
      case "pythagorean" =>
        pythagorean(args(1).toInt)
    }
  }
}
