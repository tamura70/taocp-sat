@i gb_types.w
\datethis

@*Intro. This little program outputs clauses that are satisfiable if and
only if the graph~$g$ can be $c$-colored, given $g$ and $c$.

(It generalizes {\mc SAT-PIGEONS}, which is the case where $g=K_m$
and $c=n$.)

Suppose the graph has $m$ edges and $n$ vertices. Then there are
$nc$ variables $v.k$, meaning that vertex~$v$ gets color~$k$.
And there are $n$ clauses of size~$c$ (to ensure that each vertex
gets at least one color), plus $mc$ clauses of size~2 (to ensure that
adjacent vertices don't share a color). Plus $n{c\choose2}$ ``exclusion
clauses,'' to ensure that no vertex gets more than one color.

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
  @<Generate the positive clauses@>;
  @<Generate the negative clauses@>;
  @<Generate the exclusion clauses@>;
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
printf("~ sat-color-exclusion %s %d\n",argv[1],c);

@ @<Generate the positive clauses@>=
for (v=g->vertices;v<g->vertices+g->n;v++) {
  for (k=1;k<=c;k++) printf(" %s.%d",v->name,k);
  printf("\n");
}

@ @<Generate the negative clauses@>=
for (k=1;k<=c;k++)
  for (v=g->vertices;v<g->vertices+g->n;v++)
    for (a=v->arcs;a;a=a->next)
      if (a->tip>v)
        printf("~%s.%d ~%s.%d\n",v->name,k,a->tip->name,k);

@ @<Generate the exclusion clauses@>=
for (j=1;j<=c;j++) for (k=j+1;k<=c;k++)
  for (v=g->vertices;v<g->vertices+g->n;v++)
    printf("~%s.%d ~%s.%d\n",v->name,j,v->name,k);

@*Index.
