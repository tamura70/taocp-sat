import utils.{assignments,bitvec2str,atmostR_bb}

object stuck {
  def patterns(bchain: BooleanChain, ins: Seq[String], outs: Seq[String]): Iterator[(String,String,String)] =
    for {
      assignment <- assignments(ins)
      input = ins.map(assignment(_))
      as1 = bchain.eval(assignment)
      correct = outs.map(as1(_))
      wire <- bchain.variables; if wire != ""
      st <- Seq(false,true)
      as2 = bchain.eval(assignment + (wire -> st))
      output = outs.map(as2(_))
      if output != correct
      stuck = if (st) wire else "~" + wire
    } yield (bitvec2str(input), stuck, bitvec2str(output))
  def list_patterns(bchain: BooleanChain, ins: Seq[String], outs: Seq[String]): Unit = {
    for ((pattern,stuck,output) <- patterns(bchain, ins, outs)) {
      println(pattern + " " +  stuck + " " + output)
    }
  }
  def covering(bchain: BooleanChain, ins: Seq[String], outs: Seq[String]): Unit = {
    val ps = patterns(bchain, ins, outs).toSeq
    for {
      wire <- bchain.variables; if wire != ""
      st <- Seq(false,true)
      stuck = if (st) wire else "~" + wire
    } {
      println(s"~ patterns of $stuck")
      val patterns = for ((in,s,out) <- ps; if s == stuck) yield Integer.parseInt(in, 2)
      if (! patterns.isEmpty)
        println(patterns.mkString(" "))
    }
  }
  def min_covering(bchain: BooleanChain, ins: Seq[String], outs: Seq[String], r: Int): Unit = {
    covering(bchain, ins, outs)
    val patterns = (0 until (1 << ins.size)).map(_.toString)
    atmostR_bb(patterns, r)
  }
  def main(args: Array[String]): Unit = {
    val bchain = new BooleanChain
    bchain.load(scala.io.Source.stdin)
    val ins = args(1).split(",")
    val outs = args(2).split(",")
    args(0) match {
      case "list_patterns" =>
        list_patterns(bchain, ins, outs)
      case "covering" =>
        covering(bchain, ins, outs)
      case "min_covering" =>
        min_covering(bchain, ins, outs, args(3).toInt)
    }
  }  
}
