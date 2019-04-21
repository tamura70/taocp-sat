@i gb_types.w
\datethis

@*Intro. This program reads in a gate graph (in the standard Stanford GraphBase
format as defined in {\mc GB\_GATES}) and converts it a similar graph in
which every vertex corresponds to a ``wire'' in a physical network for
the original circuit. Informally, the wires correspond to the parts of a
circuit that can be ``stuck'' or not. The main difference is that
each wire is the input to at most one subsequent gate, except for
``fanout branch'' wires; the latter are inputs to exactly two
subsequent vertices called ``clones.''

A clone vertex |v| has |v->typ='F'|. (\.F stands for fanout; the
letter \.C was already taken, to stand for a constant gate.) It
has one outgoing arc, which points to its parent. The two clones with
the same parent are consecutive. All clones descended from a normal
gate appear immediately following that gate. (Thus the $n$ inputs to the
circuit, which formerly were the first $n$ gates, are now interspersed
with their clones.)

Every wire has a ``top'' and a ``bottom.'' The top is either external
(namely one of the $n$ inputs), or the output of a previous ordinary
gate, or the implicit junction for two clones. The bottom is either
external (namely one of the $m$ outputs), or an input to a subsequent
ordinary gate, or an input to an implicit junction.

Thus the number of vertices is $n$, plus the number $A$ of ordinary gates,
plus $2B$ for the clones, where $B$ is the number of implicit junctions.
This counts the wires by the number of tops of wires.

We can also count them by the number of bottoms. Then we conclude that
the number of vertices is $m$, plus $2A$ for the inputs to ordinary
gates (if we assume that they all have exactly two inputs), plus $B$.
Equating these two counts gives $m+A=n+B$, although the relationship
will be different if ordinary gates aren't all binary. (The general
formula is $m+\Sigma A-A=n+B$, where $\Sigma A$ is the sum of in-degrees
of all ordinary gates. Notice that $A+n=\hbox{|g->n|}$ and
$\Sigma A=\hbox{|g->m|}$ in terms of the input graph; hence we're
adding $2B=2(m+\hbox{|g->m|}-\hbox{|g->n|})$ clone vertices to that graph.)

No two outputs can share the same wire, nor can a wire be associated
with more than one input port to a gate or a junction.

This program also converts a sequential circuit to a combinational
circuit, by changing all latches (|v->typ='L'|) to inputs (|v->typ='I'),
and adding them to the list of outputs.

Names of the input and output files must be given on the command line.

@c
#include "gb_graph.h"
#include "gb_gates.h"
#include "gb_save.h"
FILE *in_file, *out_file;
char buf[1000];
main (int argc, char* argv[]) {
  register int i,j,k,n,r,s;
  register Vertex *u,*v, *w;
  register Arc *a, *b, *aa;
  register Graph *g,*gg;
  @<Process the command line@>;
  @<Compute out-degrees and prepend all latches to the list of outputs@>;
  @<Create the new graph, |gg|@>;
  strcpy(gg->util_types,g->util_types);
  s=save_graph(gg,argv[2]);
  if (s) fprintf(stderr,"Output written to %s (anomalies %x!)\n",argv[2],s);
  else fprintf(stderr,"Output written to %s\n",argv[2]);
}

@ @<Process the command line@>=
if (argc!=3) {
  fprintf(stderr,"Usage: %s gates-in.gb wires-out.gb\n",argv[0]);
  exit(-1);
}
g=restore_graph(argv[1]);
if (!g) {
  fprintf(stderr,"I can't restore the graph `%s'!\n",
                      argv[1]);
  exit(-2);
}
  
@ @d deg u.I /* utility field of a vertex */

@<Compute out-degrees and prepend all latches to the list of outputs@>=
for (k=0,v=g->vertices;v<g->vertices+g->n;v++) {
  v->deg=0;
  if (v->typ=='L') {
    v->typ='I';
    a=gb_virgin_arc();
    a->next=g->outs;
    a->tip=v->alt;
    g->outs=a;
  }
  else if (v->typ!='I') {
    for (a=v->arcs;a;a=a->next)
      k++,a->tip->deg++;
  }
}
for (a=g->outs;a;a=a->next)
  k++,a->tip->deg++;

@ @<Create the new graph, |gg|@>=
gg=gb_new_graph(2*k-g->n);
if (!gg) {
  fprintf(stderr,"I couldn't create a new graph!\n");
  exit(-99);
}
make_compound_id(gg,"",g,"|wires");
for (u=g->vertices,v=gg->vertices;u<g->vertices+g->n;u++) {
  v->name=gb_save_string(u->name);
  v->typ=u->typ;
  u->alt=v;
  for (a=u->arcs;a;a=a->next) {
    w=a->tip->alt;
    a->tip->alt++;
    gb_new_arc(v,w,a->len);
  }
  k=(u->deg)-1, v++;
  for (j=0;j<k;j++) {
    sprintf(buf,"%s#%d",u->name,2*j+1);
    v->name=gb_save_string(buf);
    v->typ='F';
    gb_new_arc(v,u->alt,0);
    v++;    
    sprintf(buf,"%s#%d",u->name,2*j+2);
    v->name=gb_save_string(buf);
    v->typ='F';
    gb_new_arc(v,u->alt,0);
    v++;    
    u->alt++;
  }
}
@<Create |gg->outs|@>;

@ First we reverse (and destroy) the output list of |g|. Then we translate
it into the corresponding vertices of |gg|, reversing it again in the process.

@<Create |gg->outs|@>=
for (b=NULL,a=g->outs;a;a=aa) {
  aa=a->next;
  a->next=b;
  b=a;
}
for (;b;b=b->next) {
  a=gb_virgin_arc();
  w=b->tip;
  a->tip=w->alt;
  w->alt++;
  a->next=gg->outs;
  gg->outs=a;
}
    


@*Index.
