/*1:*/
#line 12 "./sat-eulerian-balance.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
main(int argc,char*argv[]){
register int j,k;
register Graph*g;
register Vertex*u,*v;
Vertex*utilde,*vtilde;
Arc*a,*b;
/*2:*/
#line 27 "./sat-eulerian-balance.w"

if(argc!=2){
fprintf(stderr,"Usage: %s foo.gb\n",
argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",
argv[1]);
exit(-2);
}
for(v= g->vertices;v<g->vertices+g->n;v++){
for(j= 0,a= v->arcs;a;a= a->next)j++;
if(j!=4){
fprintf(stderr,"Vertex %s has degree %d, not 4!\n",
v->name,j);
exit(-3);
}
}
utilde= g->vertices;
vtilde= utilde->arcs->tip;
printf("~ sat-eulerian-balance %s\n",
argv[1]);

/*:2*/
#line 23 "./sat-eulerian-balance.w"
;
/*3:*/
#line 52 "./sat-eulerian-balance.w"

for(u= g->vertices;u<g->vertices+g->n;u++){
for(a= u->arcs;a;a= a->next){
for(b= u->arcs;b;b= b->next)if(b!=a){
printf(" %s%s.%s",
((u==utilde)&&(b->tip==vtilde))?"~":"",
u<b->tip?u->name:b->tip->name,
u<b->tip?b->tip->name:u->name);
}
printf("\n");
for(b= u->arcs;b;b= b->next)if(b!=a){
printf(" %s%s.%s",
((u==utilde)&&(b->tip==vtilde))?"":"~",
u<b->tip?u->name:b->tip->name,
u<b->tip?b->tip->name:u->name);
}
printf("\n");
}
}

/*:3*/
#line 24 "./sat-eulerian-balance.w"
;
}

/*:1*/
