\def\adj{\mathrel{\!\mathrel-\mkern-8mu\mathrel-\mkern-8mu\mathrel-\!}}
@i gb_types.w

@*Intro. This program outputs unsatisfiable clauses based on a given
4-regular graph~$G$. Let $\tilde u\adj\tilde v$ be the first edge of~$G$;
break this edge in half by inserting a new dummy vertex. The resulting
graph~$G'$ has $2n+1$ edges. We construct clauses that essentially
force $G'$ to have equally many true edges as false edges at each of
its vertices. (That can't happen, because it would imply an Eulerian
trail of odd length in which true and false edges alternate.)

@c
#include <stdio.h>
#include <stdlib.h>
#include "gb_graph.h"
#include "gb_save.h"
main(int argc,char*argv[]) {
  register int j,k;
  register Graph *g;
  register Vertex *u,*v;
  Vertex *utilde,*vtilde;
  Arc *a,*b;
  @<Process the command line@>;
  @<Output the clauses@>;
}

@ @<Process the command line@>=
if (argc!=2) {
  fprintf(stderr,"Usage: %s foo.gb\n",
                        argv[0]);
  exit(-1);
}
g=restore_graph(argv[1]);
if (!g) {
  fprintf(stderr,"I couldn't reconstruct graph %s!\n",
                                         argv[1]);
  exit(-2);
}
for (v=g->vertices;v<g->vertices+g->n;v++) {
  for (j=0,a=v->arcs;a;a=a->next) j++;
  if (j!=4) {
    fprintf(stderr,"Vertex %s has degree %d, not 4!\n",
                                 v->name,j);
    exit(-3);
  }
}
utilde=g->vertices;
vtilde=utilde->arcs->tip;
printf("~ sat-eulerian-balance %s\n",
                       argv[1]);

@ @<Output the clauses@>=
for (u=g->vertices;u<g->vertices+g->n;u++) {
  for (a=u->arcs;a;a=a->next) {
    for (b=u->arcs;b;b=b->next) if (b!=a) {
      printf(" %s%s.%s",
                  ((u==utilde)&&(b->tip==vtilde))?"~":"",
                    u<b->tip? u->name: b->tip->name,
                    u<b->tip? b->tip->name: u->name);
    }
    printf("\n");
    for (b=u->arcs;b;b=b->next) if (b!=a) {
      printf(" %s%s.%s",
                  ((u==utilde)&&(b->tip==vtilde))?"":"~",
                    u<b->tip? u->name: b->tip->name,
                    u<b->tip? b->tip->name: u->name);
    }
    printf("\n");
  }
}                    

@*Index.
