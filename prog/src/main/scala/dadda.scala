import utils.{newBool,v}

class Bin(queue: Int = 0) {
  var bin: Map[Int,Seq[String]] = Map.empty
  def isEmpty: Boolean = bin.isEmpty
  def size(k: Int): Int = bin.getOrElse(k, Seq.empty).size
  def add(k: Int, elem: String): Unit = {
    val q0 = bin.getOrElse(k, Seq.empty)
    val q1 = queue match {
      case 0 => q0 :+ elem // FIFO
      case 1 => elem +: q0 // LIFO
    }
    bin += k -> q1
  }
  def pick(k: Int): String = {
    val (elem, rest) = (bin(k).head, bin(k).tail)
    if (rest.isEmpty)
      bin = bin - k
    else
      bin += k -> rest
    elem
  }
  def bool(p: String): String = {
    val b = newBool
    println(s"$b = $p")
    b
  }
  def dadda(str: String): Unit = {
    def z(k: Int) = s"$str$k"
    var k = 0
    while (! isEmpty) {
      while (size(k) > 0) {
        if (size(k) == 1) {
          val p = pick(k)
          println(s"${z(k)} = $p")
        } else if (size(k) == 2) {
          val b1 = bool(pick(k))
          val b2 = bool(pick(k))
          println(s"${z(k)} = $b1 xor $b2")
          add(k+1, s"$b1 and $b2")
        } else {
          val b1 = bool(pick(k))
          val b2 = bool(pick(k))
          val b3 = bool(pick(k))
          val r = bool(s"$b1 xor $b2")
          add(k, s"$r xor $b3")
          val p = bool(s"$b1 and $b2")
          val q = bool(s"$r and $b3")
          add(k+1, s"$p or $q")
        }
      }
      k += 1
    }
    k - 1
  }
}

object dadda {
  def add(bin: Bin, x: String, i0: Int, i1: Int): Unit = {
    for (i <- i0 to i1)
      bin.add(i, v(x,i))
  }
  def product(bin: Bin, x: String, i0: Int, i1: Int, y: String, j0: Int, j1: Int): Unit = {
    for (i <- i0 to i1; j <- j0 to j1)
      bin.add(i+j-1, v(x,i) + " and " + v(y,j))
  }
  def palindrome(x: String, i0: Int, i1: Int): Unit = {
    for (i <- i0 to i1; j = i0 + i1 - i; if i < j)
      println(v(x,i) + " = " + v(x,j))
  }
  def factor(queue: Int, m: Int, n: Int, zs: String): Unit = {
    val bin = new Bin(queue)
    product(bin, "X", 1, m, "Y", 1, n)
    bin.dadda("Z")
    val zr = zs.reverse
    for (i <- 1 to zr.size) zr(i-1) match {
      case '0' => println(v("Z",i) + " = 0")
      case '1' => println(v("Z",i) + " = 1")
      case _ =>
    }
  }
  def square_palindrome(m: Int, n: Int): Unit = {
    val bin = new Bin
    product(bin, "X", 1, m, "X", 1, m)
    bin.dadda("Z")
    palindrome("Z", 1, n)
    println(v("Z",n) + " = 1")
    for (i <- n+1 to 2*m)
      println(v("Z",i) + " = 0")
  }
  def square_palindrome2(m: Int, n: Int, xs: String): Unit = {
    val bin = new Bin
    product(bin, "X", 1, m, "X", 1, m)
    bin.dadda("Z")
    palindrome("Z", 1, n)
    println(v("Z",n) + " = 1")
    for (i <- n+1 to 2*m)
      println(v("Z",i) + " = 0")
    println(v("Z",1) + " = 1")
    println(v("Z",2) + " = 0")
    println(v("Z",3) + " = 0")
    if (xs != "") {
      val xr = xs.reverse
      for (i <- 1 to xr.size) xr(i-1) match {
        case '0' => println(v("X",i) + " = 0")
        case '1' => println(v("X",i) + " = 1")
        case _ =>
      }
      val z = Integer.parseInt(xs, 2)
      var zr = ("0" * xs.size + (z*z).toBinaryString).reverse
      for (i <- 1 to xr.size) zr(i-1) match {
        case '0' => println(v("Z",i) + " = 0")
        case '1' => println(v("Z",i) + " = 1")
        case _ =>
      }
    }
  }
  def tri_palindrome(k: Int, m: Int): Unit = {
    val bin = new Bin
    product(bin, "N", 1, k, "N", 1, k)
    add(bin, "N", 1, k)
    bin.dadda("TT")
    palindrome("N", 1, k)
    palindrome("TT", 2, m)
    println(v("TT", m) + " = 1")
    for (i <- m+1 to 2*k)
      println(v("TT",i) + " = 0")
  }
  def ex43(n: Int, m: Int): Unit = {
    val bin = new Bin
    product(bin, "X", 1, n, "Y", 1, n)
    bin.dadda("Z")
    palindrome("X", 1, n)
    println(v("X",1) + " = 1")
    palindrome("Y", 1, n)
    println(v("Y",1) + " = 1")
    palindrome("Z", 1, m)
    println(v("Z",1) + " = 1")
    for (i <- m+1 to 2*n)
      println(v("Z",i) + " = 0")
  }
  def main(args: Array[String]): Unit = {
    args(0) match {
      case "factor_fifo" =>
        factor(0, args(1).toInt, args(2).toInt, args(3))
      case "factor_lifo" =>
        factor(1, args(1).toInt, args(2).toInt, args(3))
      case "square_palindrome" =>
        square_palindrome(args(1).toInt, args(2).toInt)
      case "square_palindrome2" if args.size <= 3 =>
        square_palindrome2(args(1).toInt, args(2).toInt, "")
      case "square_palindrome2" =>
        square_palindrome2(args(1).toInt, args(2).toInt, args(3))
      case "tri_palindrome" =>
        tri_palindrome(args(1).toInt, args(2).toInt)
      case "ex43" =>
        ex43(args(1).toInt, args(2).toInt)
    }
  }
}
