object synth {
  def isPrime(n: Int): Boolean =
    n >= 2 && (2 to math.sqrt(n).toInt).forall(n % _ != 0)
  def data_primes(bits: Int, n: Int, negate: Boolean): Unit = {
    for (p <- 0 until n) {
      val b = if (isPrime(p) ^ negate) "1" else "0"
      val s = "0" * bits + p.toBinaryString
      println(s.substring(s.size - bits) + ":" + b)
    }
  }
  def data_life: Unit = {
    def f(n: Int): Seq[List[Int]] =
      if (n == 0) Seq(Nil)
      else for (xs <- f(n -1); x <- 0 to 1) yield xs :+ x
    for {
      xs <- f(9)
      s = 2*xs.sum - xs(4)
      xx = if (4 < s && s < 8) 1 else 0
    } println(xs.mkString("") + ":" + xx)
  }
  def data_life_sum: Unit = {
    def bits(n: Int, len: Int) = {
      val s = "1"*n + "0"*len
      s.substring(0, len)
    }
    for {
      x <- 0 to 1
      s1 <- 0 to 3; s2 <- x to x+2; s3 <- 0 to 3;
      s = 2*(s1 + s2 + s3) - x
      xx = if (4 < s && s < 8) 1 else 0
    } {
      println(x.toString + bits(s1,3) + bits(s2,3) + bits(s3,3) + ":" + xx)
    }
  }
  def main(args: Array[String]): Unit = {
    args(0) match {
      case "data_primes" =>
        data_primes(args(1).toInt, args(2).toInt, false)
      case "data_composites" =>
        data_primes(args(1).toInt, args(2).toInt, true)
      case "data_life" =>
        data_life
      case "data_life_sum" =>
        data_life_sum
    }
  }  
}
