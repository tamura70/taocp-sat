import utils.{neg,atleast1,exact1,atmostR_sinz,atmostR_bb}

object mcgregor {
  def eq(v: String, c: Int): String = s"$v.$c"
  def gcp(vertices: Seq[String], edges: Seq[(String,String)], colors: Int): Unit = {
    for (v <- vertices) {
      val xs = (1 to colors).map(c => eq(v,c))
      atleast1(xs)
      // exact1(xs)
    }
    for ((u,v) <- edges) {
      for (c <- 1 to colors)
        println(neg(eq(u,c)) + " " + neg(eq(v,c)))
    }
  }
  def mcgregor(n: Int): (Seq[String],Seq[(String,String)]) = {
    def v(j: Int, k: Int) = s"$j.$k"
    val vertices = for (j <- 0 to n; k <- 0 until n) yield v(j,k)
    var edges: Seq[(String,String)] = Seq.empty
    def e(u: String, v: String) { edges :+= (u,v) }
    for (j <- 0 to n; k <- 0 until n) {
      if (j == 1 && k == 0) {
        for (i <- n/2 until n) e(v(j, k), v(n, i))
      } else {
        if (j == 0 && k == 0) {
          e(v(j, k), v(1, 0))
          for (i <- 1 to n/2) e(v(j, k), v(n, i))
        }
        if (j < n && k < n-1) e(v(j, k), v(j+1, k+1))
        if (j == 0) e(v(j, k), v(n, n-1))
        if (j != k && j < n) e(v(j, k), v(j+1, k))
        if (j != k+1 && k < n-1) e(v(j, k), v(j, k+1))
        if (j == k && k < n-1) e(v(j, k), v(n-j, 0))
        if (j == k && j > 0) e(v(j, k), v(n+1-j, 0))
        if (k == n-1 && j > 0 && j < k) e(v(j, k), v(n-j, n-j-1))
        if (k == n-1 && j > 0 && j < n) e(v(j, k), v(n+1-j, n-j))
      }
    }
    (vertices, edges)
  }
  def graph(n: Int): Unit = {
    val (vertices, edges) = mcgregor(n)
    println(s"c McGregor graph of order $n")
    println(s"p edge ${vertices.size} ${edges.size}")
    for (v <- vertices)
      println(s"v $v")
    for ((u,v) <- edges)
      println(s"e $u $v")
  }
  def color(n: Int, colors: Int): Unit = {
    val (vertices, edges) = mcgregor(n)
    gcp(vertices, edges, colors)
  }
  def color_sinz(n: Int, colors: Int, r: Int): Unit = {
    val (vertices, edges) = mcgregor(n)
    gcp(vertices, edges, colors)
    atmostR_sinz(vertices.map(v => eq(v,1)), r)
  }
  def color_bb(n: Int, colors: Int, r: Int): Unit = {
    val (vertices, edges) = mcgregor(n)
    gcp(vertices, edges, colors)
    atmostR_bb(vertices.map(v => eq(v,1)), r)
  }
  def main(args: Array[String]): Unit = {
    args(0) match {
      case "graph" =>
        graph(args(1).toInt)
      case "color" =>
        color(args(1).toInt, args(2).toInt)
      case "color_sinz" =>
        color_sinz(args(1).toInt, args(2).toInt, args(3).toInt)
      case "color_bb" =>
        color_bb(args(1).toInt, args(2).toInt, args(3).toInt)
    }
  }
}
