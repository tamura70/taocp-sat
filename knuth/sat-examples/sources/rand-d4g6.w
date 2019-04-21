@*Intro. This experimental program tries to construct a
4-regular graph with girth $\ge6$, having a given number~$n$ of vertices.
It does this by random choices, using a method more-or-less suggested by
Exoo, McKay, Myrvold, and Nadon [{\sl J.~Discrete Algorithms\/ \bf9} (2011),
168--169]: We start with an empty graph and add one edge at a time, provided
that the new edge doesn't complete a too-short cycle. We prefer to add
an edge between two unsaturated vertices that already have the highest
possible sum of degrees.

I wrote this in a hurry, because I don't think such graphs are rare (unless
$n$ is small).

@d maxn 100 /* max potential vertices */
@d maxe ((maxn*(maxn-1))>>1) /* max potential edges */

@c
#include <stdio.h>
#include <stdlib.h>
#include "gb_flip.h"
int nn; /* the given number */
int seed; /* the given seed for pseudorandom numbers */
int e; /* the current number of edges */
@<Typedefs@>;
@<Global variables@>;
@<Subroutines@>;
main (int argc,char*argv[]) {
  register int i,j,k,s,d1,d2,u,v,w,p,t,uu;
  @<Process the command line@>;
  @<Initialize the graph to empty@>;
  for (e=0;e<2*nn;) {
    if (sanity_checking) sanity();
    for (s=6;s>=0;s--) {
      for (p=0,d1=(s>3?3:s),d2=s-d1;d1>=d2;d1--,d2++)
        @<Record each eligible edge between |u| of degree |d1|
              and |v| of degree |d2|@>;
      if (p) goto progress; /* we found |p| eligible edges */
    }
    @<Delete a random edge@>;
    e--;@+continue; /* bad luck: no edges are eligible */
progress:@+@<Insert a random eligible edge@>;
    e++;
  }
  @<Output the solution@>;
}

@ @<Process the command line@>=
if (argc!=3 || sscanf(argv[1],"%d",&nn)!=1
            || sscanf(argv[2],"%d",&seed)!=1) {
  fprintf(stderr,"Usage: %s n seed\n",argv[0]);
  exit(-1);
}
if (nn>maxn) {
  fprintf(stderr,"Recompile me: I don't allow n (%d) to exceed %d!\n",nn,maxn);
  exit(-2);
}
gb_init_rand(seed);

@*Data structures.
I'm in a mood to use sequential data structures today, so I'll leave
doubly linked lists for another day. This program has sequential lists
for (i)~the vertices of given degree, (ii)~the neighbors of a given
vertex, and (iii)~the set of all current edges. There also are
inverted lists so that we can do deletions.

For each vertex |v|, with |0<=v<nn|, there's an array |adj[v]| that
contains the |deg[v]| current neighbors of~|v|.

For each |d|, with |0<=d<=4|, there's an array |dg[d]| that lists
the |dglen[d]| vertices whose current degree is~|d|. The position
of vertex~|v| in |dg[deg[v]]| is |dginx[v]|.

@<Glob...@>=
int adj[maxn][4]; /* vertices adjacent to a given |v| */
int deg[maxn]; /* current length of |adj| entries */
int dg[5][maxn]; /* vertices having a given degree */
int dglen[5]; /* current length of |dg| entries */
int dginx[maxn]; /* where does |v| appear in the |dg| table? */

@ Each edge is captured also in a record that contains its endpoints
|u| and~|v|, together with the places |uinx|, |vinx| where they
appear within |adj[v]| and |adj[u]|.

@<Type...@>=
typedef struct {
  int u,v; /* endpoints */
  int uinx,vinx; /* inverted indices */
} edge;

@ The current edges appear in an array called |ee|. The edge that
corresponds to |adj[v][j]| appears in position |adjinx[v][j]| of this array.

Since every vertex has at most four neighbors, there are at most $2n$ edges.

@<Glob...@>=
edge ee[2*maxn]; /* the current edges */
int adjinx[maxn][4]; /* inverse indexes for edges */

@ Here's a routine that verifies all the redundant aspects of these
structures. I found it helpful when debugging (and also when first
writing the code).

@<Sub...@>=
void sanity_fail(char*m,int x,int y) {
  fprintf(stderr,"%s (%d,%d)!\n",m,x,y);
}
@#
void sanity(void) { /* check validity of the edge structures */
  register d,j,s,u,v;
  for (v=s=0;v<nn;v++) s+=deg[v];
  if (s!=2*e) sanity_fail("bad sum of degs",s,2*e);
  for (d=s=0;d<=4;d++) s+=dglen[d];
  if (s!=nn) sanity_fail("bad sum of dglens",s,nn);
  for (d=0;d<=4;d++) for (j=0;j<dglen[d];j++) {
    v=dg[d][j];
    if (deg[v]!=d) sanity_fail("bad deg",v,d);
    if (dginx[v]!=j) sanity_fail("bad dginx",v,j);
  }
  for (j=0;j<e;j++) {
    u=ee[j].u, v=ee[j].v;
    if (u!=adj[v][ee[j].uinx]) sanity_fail("bad uinx",u,v);
    if (v!=adj[u][ee[j].vinx]) sanity_fail("bad vinx",u,v);
    if (adjinx[u][ee[j].vinx]!=j) sanity_fail("bad adjinx",u,j);
    if (adjinx[v][ee[j].uinx]!=j) sanity_fail("bad adjinx",v,j);
  }
}

@ A global ``|time|'' counter advances by 1 every time we insert
or delete an edge.

The |wait| array is used to place a temporary embargo on edges that have been
deleted; such edges cannot be reinserted until |time>=wait[u][v]|.

While deciding what edge to insert next, we will build a list of all the
currently eligible ones, called |elig|.

@d sanity_checking time>=0 /* should |sanity| be checked now? */

@<Glob...@>=
int time; /* the number of updates we've made */
int wait[maxn][maxn]; /* lower bound on the time when an edge is eligible */
int uelig[maxe],velig[maxe]; /* endpoints of available choices */
int elig; /* the current number of choices */

@ @<Initialize the graph to empty@>=
e=0; /* actually |e| is already zero; but what the heck */
for (v=0;v<nn;v++) deg[v]=0,dg[0][v]=v,dginx[v]=v;
dglen[0]=nn;

@ Here's how to insert a new edge $uv$:

@<Sub...@>=
void insert(register int u,register int v) {
  register int d,j,k,w;
  ee[e].u=u,ee[e].v=v;
  @<Append |v| to |adj[u]|@>;
  @<Append |u| to |adj[v]|@>;
}

@ When increasing |deg[u]| we must move |u| from one slot in |dg| to another.

@<Append |v| to |adj[u]|@>=
d=deg[u],adj[u][d]=v,adjinx[u][d]=e,ee[e].vinx=d,deg[u]=d+1;
j=dginx[u],k=dglen[d];
w=dg[d][k-1],dg[d][j]=w,dginx[w]=j,dglen[d]=k-1; /* remove |u| from |dg[d]| */
k=dglen[d+1],dg[d+1][k]=u,dginx[u]=k,dglen[d+1]=k+1; /* put it in |dg[d+1]| */

@ And similarly, \dots$\,$.

@<Append |u| to |adj[v]|@>=
d=deg[v],adj[v][d]=u,adjinx[v][d]=e,ee[e].uinx=d,deg[v]=d+1;
j=dginx[v],k=dglen[d];
w=dg[d][k-1],dg[d][j]=w,dginx[w]=j,dglen[d]=k-1; /* remove |v| from |dg[d]| */
k=dglen[d+1],dg[d+1][k]=v,dginx[v]=k,dglen[d+1]=k+1; /* put it in |dg[d+1]| */

@ The |delete| routine goes the other way, which is a bit harder.

@<Sub...@>=
void delete(register int j) {
  register int d,i,k,u,v,ui,vi,w;
  u=ee[j].u,v=ee[j].v,ui=ee[j].uinx,vi=ee[j].vinx;
  @<Delete |u| from |adj[v]|@>;
  @<Delete |v| from |adj[u]|@>;
  @<Delete |ee[j]| from |ee|@>;
}

@ @<Delete |u| from |adj[v]|@>=
d=deg[v];
if (ui!=d-1) {
  w=adj[v][d-1],i=adjinx[v][d-1],adj[v][ui]=w,adjinx[v][ui]=i;
  if (w==ee[i].u) ee[i].uinx=ui;
  else ee[i].vinx=ui;
}
deg[v]=d-1,i=dginx[v],k=dglen[d];
w=dg[d][k-1],dg[d][i]=w,dginx[w]=i,dglen[d]=k-1; /* remove |v| from |dg[d]| */
k=dglen[d-1],dg[d-1][k]=v,dginx[v]=k,dglen[d-1]=k+1; /* put it in |dg[d-1]| */

@ @<Delete |v| from |adj[u]|@>=
d=deg[u];
if (vi!=d-1) {
  w=adj[u][d-1],i=adjinx[u][d-1],adj[u][vi]=w,adjinx[u][vi]=i;
  if (w==ee[i].u) ee[i].uinx=vi;
  else ee[i].vinx=vi;
}
deg[u]=d-1,i=dginx[u],k=dglen[d];
w=dg[d][k-1],dg[d][i]=w,dginx[w]=i,dglen[d]=k-1; /* remove |u| from |dg[d]| */
k=dglen[d-1],dg[d-1][k]=u,dginx[u]=k,dglen[d-1]=k+1; /* put it in |dg[d-1]| */

@ @<Delete |ee[j]| from |ee|@>=
if (j!=e-1) {
  u=ee[e-1].u,v=ee[e-1].v,ui=ee[e-1].uinx,vi=ee[e-1].vinx;
  ee[j]=ee[e-1];
  adjinx[v][ui]=j;
  adjinx[u][vi]=j;
}

@*Doing it. Now we've got the basic mechanisms nicely in place, so we just
need to use them.

@<Record each eligible edge between |u| of degree |d1|
              and |v| of degree |d2|@>=
if (dglen[d1] && dglen[d2]) {
  for (i=dglen[d1]-1;i>=0;i--) {
    u=dg[d1][i];
    @<Stamp all vertices at distance |<5| from |u|@>;
    for (j=(d1==d2?i-1:dglen[d2]-1);j>=0;j--) {
      v=dg[d2][j];
      if ((stamp[v]!=curstamp) && (time>=wait[u][v]))
        uelig[p]=u, velig[p]=v, p++;
    }
  }
}

@ Reachability from |u| is conveniently monitored by using a unique stamp.
We also use a |queue| for a breadth-first search.

@<Glob...@>=
int stamp[maxn]; /* the most recent stamp received by each vertex */
int curstamp;
int queue[maxn]; /* elements known to be close to |u|, in order of distance */
int vbose; /* this variable can be set positive while debugging */

@ @<Stamp all vertices at distance |<5| from |u|@>=
{
  register int front,rear,nextfront;
  curstamp++; /* advance to a unique new stamp value */
  if (curstamp==0) {
    fprintf(stderr,"Hey, you better give up!\n");
    exit(-666); /* more than four billion failures */
  }
  queue[0]=u,front=0,rear=1,stamp[u]=curstamp; /* |u| goes in the queue */
  for (k=0;k<4;k++) {
    for (nextfront=rear;front<nextfront;front++) {
      uu=queue[front]; /* a vertex at distance |k| from |u| */
      for (t=deg[uu]-1;t>=0;t--) {
        w=adj[uu][t];
        if (stamp[w]!=curstamp)
          stamp[w]=curstamp,queue[rear++]=w; /* |w| is at distance |k+1| */
      }
    }
  }
}

@ @<Insert a random eligible edge@>=
j=gb_unif_rand(p);
if (vbose)
  fprintf(stderr,"%d: Inserting %d--%d (%d,%d; %d elig)\n",
          time,uelig[j],velig[j],deg[uelig[j]],deg[velig[j]],p);
insert(uelig[j],velig[j]);
time++;

@ @d embargo 10

@<Delete a random edge@>=
j=gb_unif_rand(e);
if (vbose)
  fprintf(stderr,"%d: Deleting %d--%d (%d present)\n",
    time,ee[j].u,ee[j].v,e);
delete(j);
wait[ee[j].u][ee[j].v]=wait[ee[j].v][ee[j].u]=time+embargo;

@ @<Output the solution@>=
for (j=0;j<e;j++)
  printf("%d %d\n",ee[j].u,ee[j].v);

@*Index.
