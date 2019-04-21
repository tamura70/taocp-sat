@i gb_types.w

@*Intro. Standard input contains a list of pairs of positive integers.
We set \.{/tmp/ez.gb} to the (undirected) graph with those edges.

@d maxm 10000

@c
#include <stdio.h>
#include <stdlib.h>
#include "gb_graph.h"
#include "gb_save.h"
#include "gb_basic.h"
unsigned int u[maxm],v[maxm];
main() {
  Graph *g;
  register int k;
  unsigned int nn;
  for (k=0,nn=0;k<maxm;k++) {
    if (scanf("%u %u", &u[k], &v[k])!=2) break;
    if (u[k]>nn) nn=u[k];
    if (v[k]>nn) nn=v[k];
  }
  if (k==maxm) {
    fprintf(stderr,"Sorry, I can handle only %d edges!\n",maxm);
    exit(-1);
  }
  g=empty(nn+1);
  for (k--;k>=0;k--) gb_new_edge(g->vertices+u[k],g->vertices+v[k],1);
  save_graph(g,"/tmp/ez.gb");
  printf("Created graph /tmp/ez.gb with %ld vertices and %ld edges.\n",
            g->n,g->m/2);
}

@*Index.
