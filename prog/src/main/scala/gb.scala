import scala.io.Source
import scala.collection.SortedMap
import utils.{neg}

class GBGraph {
  var name = ""
  var utils: String = ""
  var vertices: SortedMap[Int,Vertex] = SortedMap.empty
  var arcs: SortedMap[Int,Arc] = SortedMap.empty
  case class Vertex(id: Int) {
    var name: String = ""
    var outArcs: Seq[Arc] = Seq.empty
    var inArcs: Seq[Arc] = Seq.empty
    var utils: String = ""
    override def toString = s"V$id: $name, $utils"
  }
  case class Arc(id: Int) {
    var from: Vertex = null
    var to: Vertex = null
    var utils: String = ""
    override def toString = s"A$id: V${from.id} -> V${to.id}, $utils"
  }
  def newVertex(id: Int): Vertex =
    vertices.getOrElse(id, {
      val v = Vertex(id); vertices += id -> v; v
    })
  def newArc(id: Int): Arc =
    arcs.getOrElse(id, {
      val a = Arc(id); arcs += id -> a; a
    })
  def load(source: Source): Unit = {
    val lines: Iterator[String] = {
      val it = source.getLines
      new Iterator[String] {
        def hasNext = it.hasNext
        def next = {
          val l = it.next
          if (l.endsWith("\\")) l.dropRight(1) + next
          else l
        }
      }
    }
    var vLines = 0
    var aLines = 0
    val re0 = """\* GraphBase graph \(util_types ([A-Z]+),(\d+)V,(\d+)A\)""".r
    lines.next match {
      case re0(s1,s2,s3) => {
        vLines = s2.toInt; aLines = s3.toInt
      }
    }
    var n = 0
    var m = 0
    val re1 = "\"([^\"]+)\",(\\d+),(\\d+),?(.*)".r
    lines.next match {
      case re1(s1,s2,s3,s4) => {
        name = s1; n = s2.toInt; m = s3.toInt; utils = s4
      }
    }
    require(lines.next == "* Vertices")
    val re2 = "\"([^\"]+)\",(A?)(\\d+),?(.*)".r
    for (id <- 0 until vLines; line = lines.next; if id < n) {
      line match {
        case re2(s1,s2,s3,s4) => {
          val v = newVertex(id)
          v.name = s1; v.utils = s4
          if (s2 == "A") {
            val a = newArc(s3.toInt); a.from = v
            v.outArcs = Seq(a)
          } else {
            require(s3 == "0")
          }
        }
      }
    }
    require(lines.next == "* Arcs")
    var next: Map[Arc,Arc] = Map.empty
    val re3 = "V(\\d+),(A?)(\\d+),?(.*)".r
    for (id <- 0 until aLines; line = lines.next; if id < m) {
      line match {
        case re3(s1,s2,s3,s4) => {
          val a = newArc(id)
          a.to = vertices(s1.toInt); a.utils = s4
          if (s2 == "A") {
            next += a -> newArc(s3.toInt)
          } else {
            require(s3 == "0")
          }
        }
      }
    }
    for ((id,v) <- vertices; if ! v.outArcs.isEmpty) {
      def getArcs(a: Arc, arcs: Seq[Arc]): Seq[Arc] =
        if (! next.contains(a)) a +: arcs else getArcs(next(a), a +: arcs)
      v.outArcs = getArcs(v.outArcs.head, Seq.empty)
      for (a <- v.outArcs)
        a.from = v
    }
    for ((id,v) <- vertices)
      v.inArcs = arcs.values.toSeq.filter(a => a.to == v)
    require(lines.next.startsWith("* Checksum"))
  }
  override def toString = {
    vertices.values.mkString("", "\n", "\n") + arcs.values.mkString("", "\n", "\n")
  }
}

object GBGraphMain {
  def gates2bchain(gb: GBGraph): Unit = {
    for ((_,v) <- gb.vertices) {
      val name = v.name
      val op = v.utils.split(",")(1).toInt.toChar
      val args = v.outArcs.map(_.to.name).reverse
      (op, args) match {
        case ('I', Seq()) => println(s"~ Input $name")
        case ('F', Seq(x)) => println(s"$name = $x")
        case ('~', Seq(x)) => println(s"$name = ${neg(x)}")
        case ('&', Seq(x,y)) => println(s"$name = $x and $y")
        case ('|', Seq(x,y)) => println(s"$name = $x or $y")
        case ('^', Seq(x,y)) => println(s"$name = $x xor $y")
      }
      if (v.inArcs.isEmpty)
        println(s"~ Output $name")
    }
  }

  def main(args: Array[String]): Unit = {
    val gb = new GBGraph
    gb.load(Source.fromFile(args(1)))
    args(0) match {
      case "print" =>
        println(gb)
      case "gates2bchain" =>
        gates2bchain(gb)
    }
  }
}
