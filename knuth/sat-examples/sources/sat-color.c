/*1:*/
#line 16 "./sat-color.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
int c;
main(int argc,char*argv[]){
register int i,j,k;
register Arc*a;
register Graph*g;
register Vertex*v;
/*2:*/
#line 32 "./sat-color.w"

if(argc!=3||sscanf(argv[2],"%d",&c)!=1){
fprintf(stderr,"Usage: %s foo.gb c\n",argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
exit(-2);
}
if(c<=0){
fprintf(stderr,"c must be positive!\n");
exit(-3);
}
printf("~ sat-color %s %d\n",argv[1],c);

/*:2*/
#line 27 "./sat-color.w"
;
/*3:*/
#line 48 "./sat-color.w"

for(v= g->vertices;v<g->vertices+g->n;v++){
for(k= 1;k<=c;k++)printf(" %s.%d",v->name,k);
printf("\n");
}

/*:3*/
#line 28 "./sat-color.w"
;
/*4:*/
#line 54 "./sat-color.w"

for(k= 1;k<=c;k++)
for(v= g->vertices;v<g->vertices+g->n;v++)
for(a= v->arcs;a;a= a->next)
if(a->tip> v)
printf("~%s.%d ~%s.%d\n",v->name,k,a->tip->name,k);

/*:4*/
#line 29 "./sat-color.w"
;
}

/*:1*/
