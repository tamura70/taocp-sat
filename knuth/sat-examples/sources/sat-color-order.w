@i gb_types.w
\datethis

@*Intro. This little program outputs clauses that are satisfiable if and
only if the graph~$g$ can be $c$-colored, given $g$ and $c$.

(It generalizes {\mc SAT-PIGEONS}, which is the case where $g=K_m$
and $c=n$, and uses the ``order encoding.'')

Suppose the graph has $m$ edges and $n$ vertices. Then there are
$n(c-1)$ variables \.{$v$<$k$}, meaning that vertex~$v$ gets color~$<k$.
And there are $n(c-2)$ clauses of size~2 (to enforce the linear ordering
of colors), plus $mc$ clauses of size~4 (to ensure that
adjacent vertices don't share a color).

@c
#include <stdio.h>
#include <stdlib.h>
#include "gb_graph.h"
#include "gb_save.h"
int c;
main(int argc, char*argv[]) {
  register int i,j,k;
  register Arc *a;
  register Graph *g;
  register Vertex *v;
  @<Process the command line@>;
  @<Generate the ordering clauses@>;
  @<Generate the graph-coloring clauses@>;
}

@ @<Process the command line@>=
if (argc!=3 || sscanf(argv[2],"%d",&c)!=1) {
  fprintf(stderr,"Usage: %s foo.gb c\n",argv[0]);
  exit(-1);
}
g=restore_graph(argv[1]);
if (!g) {
  fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
  exit(-2);
}
if (c<=0) {
  fprintf(stderr,"c must be positive!\n");
  exit(-3);
}
printf("~ sat-color-order %s %d\n",argv[1],c);

@ @<Generate the ordering clauses@>=
for (v=g->vertices;v<g->vertices+g->n;v++)
  for (k=2;k<c;k++) printf("~%s<%d %s<%d\n",
                            v->name,k-1,v->name,k);

@ @<Generate the graph-coloring clauses@>=
for (v=g->vertices;v<g->vertices+g->n;v++)
  for (a=v->arcs;a;a=a->next) if (a->tip>v)
    for (k=1;k<=c;k++) {
      if (k==1) printf("~%s<%d ~%s<%d\n",
                       v->name,k,a->tip->name,k);
      else if (k<c) printf("%s<%d ~%s<%d %s<%d ~%s<%d\n",
                       v->name,k-1,v->name,k,
                       a->tip->name,k-1,a->tip->name,k);
      else printf("%s<%d %s<%d\n",
                 v->name,k-1,a->tip->name,k-1);
    }

@*Index.
