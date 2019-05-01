import scala.sys.process.Process
object bash {
  def !(cmd: String): Int = Process(Seq("bash", "-c", cmd)).!
  def !!(cmd: String): String = Process(Seq("bash", "-c", cmd)).!!
}
def out(fileName: String)(block: => Unit): Unit = {
  val o = new java.io.PrintStream(fileName)
  Console.withOut(o) { block }
  o.close
}
def neg(lit: String) = if (lit.startsWith("~")) lit.drop(1) else "~" + lit
def values(lits: Seq[String], model: String): Seq[Int] = {
  val m = model.split("\\s+").map(x => {
    if (x.startsWith("~")) x.drop(1) -> 0 else x -> 1
  }).toMap
  lits.map(lit => m.getOrElse(lit, m(neg(lit))))
}
