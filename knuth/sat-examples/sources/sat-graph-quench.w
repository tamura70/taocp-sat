@i gb_types.w
\def\adj{\mathrel{\!\mathrel-\mkern-8mu\mathrel-\mkern-8mu\mathrel-\!}}
\datethis

@*Intro. This little program outputs clauses that are satisfiable if and
only if the graph~$g$ can be ``quenched.''

Namely, a graph on one vertex can always be quenched. A graph on vertices
$(v_1,\ldots,v_n)$ can also be quenched if there's a $k$ with
$1\le k<n$ such that $v_k\adj v_{k+1}$ and the graph on
$(v_1,\ldots,v_{k-1},v_{k+1},\ldots,v_n)$ can be quenched;
or if there's a $k$ with $1\le k<n-2$ such that $v_k\adj v_{k+3}$ and
the graph on $(v_1,\ldots,v_{k-1},v_{k+3},v_{k+1},v_{k+2},v_{k+4},\ldots,v_n)$
can be quenched.

Thus the ordering of vertices is highly significant. Quenchability is
a monotone property of the adjacency matrix. A quenchable graph is
always connected. For each $n$ there exists a set of I-know-not-how-many
labeled spanning trees such that $G$ is connected if and only if it contains
one of these spanning trees. (Those spanning trees correspond to the
prime implicants of the quenchability function. When $n=4$ there are
six of them: $1\adj2\adj3\adj4$, $1\adj2\adj4\adj3$, $1\adj4\adj2\adj3$,
$1\adj4\adj3\adj2$, or the stars centered on 3 or~4. 

The variables of the corresponding clauses are of several kinds:
(i)~$\.{tij}$ means that $v_i\adj v_j$ at time~$t$, for $0\le i<j<n-t$;
(ii)~\.{$t$Q$k$} means that a quenching move of the first kind is
used to get to time $t+1$;
(iii)~\.{$t$S$k$} means that a quenching move of the second kind
(``skip two'') is used to get to time~$t+1$. In each of these cases
the number $t$, $i$, $j$, $k$ are represented as two hexadecimal digits,
because I assume that $n\le256$.

@d nmax 256

@c
#include <stdio.h>
#include <stdlib.h>
#include "gb_graph.h"
#include "gb_save.h"
main(int argc, char*argv[]) {
  register int i,j,k,t,n;
  register Arc *a;
  register Graph *g;
  register Vertex *v,*w;
  @<Process the command line@>;
  @<Specify the initial nonadjacencies@>;
  @<Generate the possible-move clauses@>;
  @<Generate the enabling clauses@>;
  @<Generate the transition clauses@>;
}

@ @<Process the command line@>=
if (argc!=2) {
  fprintf(stderr,"Usage: %s foo.gb\n",argv[0]);
  exit(-1);
}
g=restore_graph(argv[1]);
if (!g) {
  fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
  exit(-2);
}
n=g->n;
if (n>nmax) {
  fprintf(stderr,"Sorry, that graph has too many vertices (%d>%d)!\n",
                                             n,nmax);
  exit(-3);
}
printf("~ sat-graph-quench %s\n",argv[1]);

@ It's not necessary to assert anything at time~0 when vertices are
adjacent, because of monotonicity. (Such variables \.{00$ij$} would
be pure literals and might as well be true.) But when vertices $v_i$ and $v_j$
are {\it not\/} adjacent, we must make \.{00$ij$} false.

@d stamp u.I

@<Specify the initial nonadjacencies@>=
for (v=g->vertices;v<g->vertices+n;v++) v->stamp=0;
for (v=g->vertices,j=1;v<g->vertices+n;v++,j++) {
  for (a=v->arcs;a;a=a->next) if (a->tip>v)
    a->tip->stamp=j;
  for (w=v+1;w<g->vertices+n;w++) if (w->stamp!=j)
    printf("~00%02x%02x\n",
                (unsigned int)(v-g->vertices),(unsigned int)(w-g->vertices));
}

@ @<Generate the possible-move clauses@>=
for (t=0;t<n-1;t++) {
  for (k=1;k<n-t;k++) printf(" %02xQ%02x",
                                    t,k-1);
  for (k=1;k<n-t-2;k++) printf(" %02xS%02x",
                                    t,k-1);
  printf("\n");
}

@ @<Generate the enabling clauses@>=
for (t=0;t<n-1;t++) {
  for (k=1;k<n-t;k++) printf("~%02xQ%02x %02x%02x%02x\n",
                            t,k-1,t,k-1,k);
  for (k=1;k<n-t-2;k++) printf("~%02xS%02x %02x%02x%02x\n",
                            t,k-1,t,k-1,k+2);
}
                          
@ @<Generate the transition clauses@>=
for (t=0;t<n-1;t++) {
  for (k=1;k<n-t;k++)
    for (i=1;i<n-t;i++) for (j=i+1;j<n-t;j++)
      printf("~%02xQ%02x ~%02x%02x%02x %02x%02x%02x\n",
        t,k-1,t+1,i-1,j-1,t,i<k?i-1:i,j<k?j-1:j);
  for (k=1;k<n-t-2;k++)
    for (i=1;i<n-t;i++) for (j=i+1;j<n-t;j++) {
      register iprev=(i==k? i+2: i<k+3? i-1: i),
               jprev=(j==k? j+2: j<k+3? j-1: j);
      printf("~%02xS%02x ~%02x%02x%02x %02x%02x%02x\n",
        t,k-1,t+1,i-1,j-1,t,iprev<jprev?iprev:jprev,iprev<jprev?jprev:iprev);
  }
}      

@*Index.
