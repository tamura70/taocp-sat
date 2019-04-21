/*1:*/
#line 16 "./sat-color-order.w"

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
#line 32 "./sat-color-order.w"

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
printf("~ sat-color-order %s %d\n",argv[1],c);

/*:2*/
#line 27 "./sat-color-order.w"
;
/*3:*/
#line 48 "./sat-color-order.w"

for(v= g->vertices;v<g->vertices+g->n;v++)
for(k= 2;k<c;k++)printf("~%s<%d %s<%d\n",
v->name,k-1,v->name,k);

/*:3*/
#line 28 "./sat-color-order.w"
;
/*4:*/
#line 53 "./sat-color-order.w"

for(v= g->vertices;v<g->vertices+g->n;v++)
for(a= v->arcs;a;a= a->next)if(a->tip> v)
for(k= 1;k<=c;k++){
if(k==1)printf("~%s<%d ~%s<%d\n",
v->name,k,a->tip->name,k);
else if(k<c)printf("%s<%d ~%s<%d %s<%d ~%s<%d\n",
v->name,k-1,v->name,k,
a->tip->name,k-1,a->tip->name,k);
else printf("%s<%d %s<%d\n",
v->name,k-1,a->tip->name,k-1);
}

/*:4*/
#line 29 "./sat-color-order.w"
;
}

/*:1*/
