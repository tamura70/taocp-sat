#define maxm 10000 \

/*1:*/
#line 8 "./ezgraph.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
#include "gb_basic.h"
unsigned int u[maxm],v[maxm];
#line 12 "./ezgraph-named.ch"
char fname[20];
FILE*infile;
main(int argc,char*argv[]){
#line 16 "./ezgraph.w"
Graph*g;
register int k;
unsigned int nn;
#line 20 "./ezgraph-named.ch"
if(argc!=2){
fprintf(stderr,"Usage: %s foo\n",argv[0]);
exit(-1);
}
sprintf(fname,"%s.dat",argv[1]);
infile= fopen(fname,"r");
if(!infile){
fprintf(stderr,"I can't read file `%s'!\n",fname);
exit(-2);
}
for(k= 0,nn= 0;k<maxm;k++){
if(fscanf(infile,"%u %u",&u[k],&v[k])!=2)break;
#line 21 "./ezgraph.w"
if(u[k]> nn)nn= u[k];
if(v[k]> nn)nn= v[k];
}
if(k==maxm){
fprintf(stderr,"Sorry, I can handle only %d edges!\n",maxm);
exit(-1);
}
g= empty(nn+1);
for(k--;k>=0;k--)gb_new_edge(g->vertices+u[k],g->vertices+v[k],1);
#line 37 "./ezgraph-named.ch"
sprintf(g->id,"ezgraph %s",argv[1]);
sprintf(fname,"%s.gb",argv[1]);
save_graph(g,fname);
printf("Created graph %s with %ld vertices and %ld edges.\n",fname,
#line 32 "./ezgraph.w"
g->n,g->m/2);
}

/*:1*/
