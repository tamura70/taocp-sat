@x a change file for GRAPH-CYC
run through all of these possibilities.
@y
run through all of these possibilities.

Each cycle is output as a symmetry-breaking endomorphism for clauses
that come from, say, {\mc SAT-TSEYTIN}, using the ideas in exercise
7.2.2.2--473.

A random seed is given on the command line, to establish a random total
ordering of the vertices.
@z
@x
#include "gb_save.h"
@y
#include "gb_save.h"
#include "gb_flip.h"
int seed;
@z
@x
  @<Process the command line@>;
@y
  @<Process the command line@>;
  @<Set up the random total order@>;
@z
@x
@ @<Process the command line@>=
if (argc!=3 || sscanf(argv[2],"%d",&kk)!=1) {
  fprintf(stderr,"Usage: %s foo.gb k\n",
@y
@ @<Process the command line@>=
if (argc!=4 || sscanf(argv[2],"%d",&kk)!=1 || sscanf(argv[3],"%d",&seed)!=1) {
  fprintf(stderr,"Usage: %s foo.gb k seed\n",
@z
@x
    for (j=0;j<kk;j++) printf(" %s",
                         vv[j]->name);
@y
    @<Output the cycle as a symmetry-breaking clause@>;
@z
@x
@*Index.
@y
@ @d rrank y.I

@<Set up the random total order@>=
gb_init_rand(seed);
for (v=g->vertices;v<g->vertices+g->n;v++) v->rrank=gb_next_rand();
printf("~ sat-graph-cyc %s %d %d\n",argv[1],kk,seed);

@ @<Output the cycle as a symmetry-breaking clause@>=
vv[kk]=vv[0], vv[kk+1]=vv[1];
for (i=1,j=2;j<=kk;j++) if (vv[j]->rrank>vv[i]->rrank) i=j;
if (vv[i+1]->rrank>vv[i-1]->rrank) {
  for (j=i;j<kk;j++)
    printf(" %s%s.%s",
            (j-i)&1?"":"~",
              vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
              vv[j]>vv[j+1]?vv[j]->name:vv[j+1]->name);
  for (j=0;j<i;j++)
    printf(" %s%s.%s",
            (j-i)&1?"":"~",
              vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
              vv[j]>vv[j+1]?vv[j]->name:vv[j+1]->name);
}@+else {
  for (j=i;j<kk;j++)
    printf(" %s%s.%s",
            (j-i)&1?"~":"",
              vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
              vv[j]>vv[j+1]?vv[j]->name:vv[j+1]->name);
  for (j=0;j<i;j++)
    printf(" %s%s.%s",
            (j-i)&1?"~":"",
              vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
              vv[j]>vv[j+1]?vv[j]->name:vv[j+1]->name);
}

@*Index.
@z
