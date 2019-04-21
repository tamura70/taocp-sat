@x
With change files we can change the names of the variables $x_i$.
@y
This version inputs a graph (specified as a third parameter) and
and color number (specified fourth). The output clauses will limit
the number of vertices of that color.
@z
@x
int n,r; /* the given parameters */
@y
#include "gb_graph.h"
#include "gb_save.h"
int n,r,kk; /* the given parameters */
@z
@x
  register int i,j,k,jl,jr,t,tl,tr;
@y
  register int i,j,k,jl,jr,t,tl,tr;
  Graph *g;
@z
@x
if (argc!=3 || sscanf(argv[1],"%d",&n)!=1 || sscanf(argv[2],"%d",&r)!=1) {
  fprintf(stderr,"Usage: %s n r\n",argv[0]);
  exit(-1);
}
@y
if (argc!=5 || sscanf(argv[1],"%d",&n)!=1 || sscanf(argv[2],"%d",&r)!=1 ||
      sscanf(argv[4],"%d",&kk)!=1) {
  fprintf(stderr,"Usage: %s n r foo.gb k\n",argv[0]);
  exit(-1);
}
g=restore_graph(argv[3]);
if (!g) {
  fprintf(stderr,"I can't input the graph `%s'!\n",argv[3]);
  exit(-2);
}
if (g->n!=n)
  fprintf(stderr,"Warning: The graph has %ld vertices, not %d!\n",g->n,n);
@z
@x
@d xbar(k) printf("~x%d",(k)-n+2)
@y
@d xbar(k) printf("~%s.%d",(g->vertices+(k)-n+1)->name,kk)
@z
