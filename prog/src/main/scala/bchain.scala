import scala.io.Source
import utils.{neg,value}

class BooleanChain {
  var chain: Seq[Seq[String]] = Seq.empty
  def add(xs: Seq[String]): Unit = {
    chain :+= xs
  }
  def add(line: String): Unit = {
    val re1 = """~ (.*)""".r
    val re2 = """; (.*)""".r
    val re3 = """(\S+)\s+=\s+(~?\S+)""".r
    val re4 = """(\S+)\s+=\s+(~?\S+)\s+(and|or|xor)\s+(~?\S+)""".r
    line match {
      case re1(msg) => add(Seq("~", msg))
      case re2(clause) => add(Seq(";", clause))
      case re3(z, x) => add(Seq("", z, x))
      case re4(z, x, op, y) => add(Seq(op, z, x, y))
    }
  }
  def load(source: Source): Unit = {
    for (line <- source.getLines)
      add(line)
  }
  def variables = chain.map {
    case Seq("~", _) => ""
    case Seq(";", _) => ""
    case Seq("", z, _) => z
    case Seq(op, z, _, _) => z
  }
  def encode(xs: Seq[String]): Unit = {
    xs match {
      case Seq("~", msg) => println("~ " + msg)
      case Seq(";", clause) => println(clause)
      case Seq("", z, "0") => println(neg(z))
      case Seq("", z, "1") => println(z)
      case Seq("and", z, "0", y) => encode(Seq("", z, "0"))
      case Seq("and", z, x, "0") => encode(Seq("", z, "0"))
      case Seq("and", z, "1", y) => encode(Seq("", z, y))
      case Seq("and", z, x, "1") => encode(Seq("", z, x))
      case Seq("or", z, "0", y) => encode(Seq("", z, y))
      case Seq("or", z, x, "0") => encode(Seq("", z, x))
      case Seq("or", z, "1", y) => encode(Seq("", z, "1"))
      case Seq("or", z, x, "1") => encode(Seq("", z, "1"))
      case Seq("xor", z, "0", y) => encode(Seq("", z, y))
      case Seq("xor", z, x, "0") => encode(Seq("", z, x))
      case Seq("xor", z, "1", y) => encode(Seq("", z, neg(y)))
      case Seq("xor", z, x, "1") => encode(Seq("", z, neg(x)))
      case Seq("", z, x) => {
        println(s"$x ~$z")
        println(s"${neg(x)} $z")
      }
      case Seq("and", z, x, y) => {
        println(s"$x ~$z")
        println(s"$y ~$z")
        println(s"${neg(x)} ${neg(y)} $z")
      }
      case Seq("or", z, x, y) => {
        println(s"${neg(x)} $z")
        println(s"${neg(y)} $z")
        println(s"$x $y ~$z")
      }
      case Seq("xor", z, x, y) => {
        println(s"${neg(x)} $y $z")
        println(s"$x ${neg(y)} $z")
        println(s"$x $y ~$z")
        println(s"${neg(x)} ${neg(y)} ~$z")
      }
    }
  }
  def encode: Unit = {
    for (xs <- chain)
      encode(xs)
  }
  def eval(xs: Seq[String], assignment: Map[String,Boolean]): Map[String,Boolean] =
    xs match {
      case Seq("~", msg) => assignment
      case Seq(";", clause) => assignment
      case Seq(_, z, _) if assignment.contains(z) => assignment
      case Seq(_, z, _, _) if assignment.contains(z) => assignment
      case Seq("", z, x) =>
        assignment + (z -> value(x, assignment))
      case Seq("and", z, x, y) =>
        assignment + (z -> (value(x, assignment) && value(y, assignment)))
      case Seq("or", z, x, y) =>
        assignment + (z -> (value(x, assignment) || value(y, assignment)))
      case Seq("xor", z, x, y) =>
        assignment + (z -> (value(x, assignment) != value(y, assignment)))
    }
  def eval(assignment: Map[String,Boolean]): Map[String,Boolean] = {
    var e = assignment
    for (xs <- chain)
      e = eval(xs, e)
    e
  }
  def eval(lits: Seq[String]): Unit =  {
    var assignment: Map[String,Boolean] = Map.empty
    for (lit <- lits) {
      if (lit.startsWith("~")) assignment += lit.substring(1) -> false
      else assignment += lit -> true
    }
    assignment = eval(assignment)
    val s = for ((v,value) <- assignment)
            yield (if (value) "" else "~") + v
    println(s.mkString(" "))
  }
}

object bchain {
  def encode(): Unit = {
    val bchain = new BooleanChain
    bchain.load(Source.stdin)
    bchain.encode
  }
  def eval(lits: Seq[String]): Unit = {
    val bchain = new BooleanChain
    bchain.load(Source.stdin)
    bchain.eval(lits)
  }
  def main(args: Array[String]): Unit = {
    args(0) match {
      case "encode" =>
        encode
      case "eval" =>
        eval(args.drop(1))
    }
  }  
}
