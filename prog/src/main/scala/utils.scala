object utils {
  def neg(lit: String): String =
    if (lit.startsWith("~")) lit.substring(1) else "~" + lit
  def value(lit: String, assignment: Map[String,Boolean]): Boolean =
    lit match {
      case "0" => false
      case "1" => true
      case _ if lit.startsWith("~") => ! assignment(lit.substring(1))
      case _ => assignment(lit)
    }
  def assignments(xs: Seq[String]): Iterator[Map[String,Boolean]] =
    for (p <- (0 until (1 << xs.size)).toIterator)
    yield {
      val s = p.toBinaryString.reverse
      val as = for {
        i <- 0 until xs.size
        b = if (i >= s.size || s(i) == '0') false else true
      } yield xs(i) -> b
      as.toMap
    }
  def bitvec2str(bs: Seq[Boolean]): String = bs.map(if (_) 1 else 0).mkString("")

  var bcount = 0
  def newBool: String = { bcount += 1; s"_$bcount" }
  def v(x: String, i: Int): String = s"$x$i"
  def v(x: String, i: Int, j: Int): String = s"$x${i}_$j"
  def atleast1(lits: Seq[String]): Unit = {
    println(lits.mkString(" "))
  }
  def atmost1(lits: Seq[String]): Unit = {
    for (Seq(lit1,lit2) <- lits.combinations(2))
      println(neg(lit1) + " " + neg(lit2))
  }
  def exact1(lits: Seq[String]): Unit = {
    atleast1(lits)
    atmost1(lits)
  }
  def atmost1_heule(lits: Seq[String]): Unit = {
    if (lits.size <= 4) {
      for (Seq(lit1,lit2) <- lits.combinations(2))
        println(neg(lit1) + " " + neg(lit2))
    } else {
      val t = newBool
      atmost1(lits.take(3) :+ t)
      atmost1(neg(t) +: lits.drop(3))
    }
  }
  def exact1_heule(lits: Seq[String]): Unit = {
    atleast1(lits)
    atmost1_heule(lits)
  }
  def atmost1_aspvall(lits: Seq[String]): Unit = {
    val p = lits.size
    if (p <= 3) {
      atmost1(lits)
    } else {
      val tt = for (j <- 2 to p-2) yield newBool
      def y(j: Int) = lits(j - 1)
      def t(j: Int) = j match {
        case 1 => neg(y(1))
        case _ if j == p - 1 => y(p)
        case _ => tt(j-2)
      }
      for (j <- 2 until p) {
        println(t(j-1) + " " + neg(y(j)))
        println(t(j-1) + " " + neg(t(j)))
        println(neg(y(j)) + " " + neg(t(j)))
      }
    }
  }
  def exact1_aspvall(lits: Seq[String]): Unit = {
    atleast1(lits)
    atmost1_aspvall(lits)
  }
  def atleastR(lits: Seq[String], r: Int): Unit = {
    atmostR(lits.map(neg(_)), lits.size - r)
  }
  def atmostR(lits: Seq[String], r: Int): Unit = {
    for (lits1 <- lits.combinations(r))
      println(lits1.map(neg(_)).mkString(" "))
  }
  def exactR(lits: Seq[String], r: Int): Unit = {
    atleastR(lits, r)
    atmostR(lits, r)
  }
  def atleastR_sinz(lits: Seq[String], r: Int): Unit = {
    atmostR_sinz(lits.map(neg(_)), lits.size - r)
  }
  def atmostR_sinz(lits: Seq[String], r: Int): Unit = {
    val n = lits.size
    val s = {
      for (j <- 1 to n - r; k <- 1 to r)
      yield (j,k) -> newBool
    }.toMap
    for (j <- 1 until n - r; k <- 1 to r)
      println(neg(s(j,k)) + " " + s(j+1,k))
    def x(i: Int) = lits(i - 1)
    for (j <- 1 to n - r; k <- 0 to r)
      if (k == 0)
        println(neg(x(j+k)) + " " + s(j,k+1))
      else if (k == r)
        println(neg(x(j+k)) + " " + neg(s(j,k)))
      else
        println(neg(x(j+k)) + " " + neg(s(j,k)) + " " + s(j,k+1))
  }
  def exactR_sinz(lits: Seq[String], r: Int): Unit = {
    atleastR_sinz(lits, r)
    atmostR_sinz(lits, r)
  }
  def atleastR_bb(lits: Seq[String], r: Int): Unit = {
    atmostR_bb(lits.map(neg(_)), lits.size - r)
  }
  def atmostR_bb(lits: Seq[String], r: Int): Unit = {
    val n = lits.size
    def count(k: Int): Int =
      if (k >= n) 1 else count(2*k) + count(2*k+1)
    def t(k: Int) = math.min(r, count(k))
    val bb = {
      for (k <- 2 until n; j <- 1 to t(k))
      yield (j,k) -> newBool
    }.toMap
    def b(j: Int, k: Int) =
      if (j == 1 && k >= n) Some(lits(k-n))
      else if (j == 0 || j == r+1) None
      else Some(bb(j,k))
    def Neg(lit: Option[String]) = lit.map(neg)
    for {
      k <- 2 until n; i <- 0 to t(2*k); j <- 0 to t(2*k+1)
      if 1 <= i+j && i+j <= t(k)+1
    } {
      val c = Neg(b(i,2*k)) ++ Neg(b(j,2*k+1)) ++ b(i+j,k)
      println(c.mkString(" "))
    }
    for (i <- 0 to t(2); j <- 0 to t(3); if i+j == r+1) {
      val c = Neg(b(i,2)) ++ Neg(b(j,3))
      println(c.mkString(" "))
    }
  }
  def exactR_bb(lits: Seq[String], r: Int): Unit = {
    atleastR_bb(lits, r)
    atmostR_bb(lits, r)
  }
}
