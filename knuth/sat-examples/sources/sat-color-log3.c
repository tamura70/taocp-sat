/*1:*/
#line 22 "./sat-color-log3.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
int c;
main(int argc,char*argv[]){
register int i,k,kk,t;
register Arc*a;
register Graph*g;
register Vertex*u,*v;
/*2:*/
#line 42 "./sat-color-log3.w"

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
printf("~ sat-color-log3 %s %d\n",argv[1],c);

/*:2*/
#line 33 "./sat-color-log3.w"
;
for(t= 0;c> (1<<t);t++);
for(v= g->vertices;v<g->vertices+g->n;v++)for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u<v)
/*3:*/
#line 58 "./sat-color-log3.w"

{
for(k= c;k<c+c;k++){
for(i= t,kk= k;i;i--)
if(i<t||k>=(1<<t)){
printf(" %s%s.%d %s%s.%d",
kk&1?"~":"",u->name,i,kk&1?"~":"",v->name,i);
kk>>= 1;
}
printf("\n");
}
}

/*:3*/
#line 38 "./sat-color-log3.w"
;
}
}

/*:1*/
