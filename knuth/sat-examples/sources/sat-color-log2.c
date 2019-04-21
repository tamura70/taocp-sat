/*1:*/
#line 21 "./sat-color-log2.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
int c;
main(int argc,char*argv[]){
register int i,k,t;
register Arc*a;
register Graph*g;
register Vertex*u,*v;
/*2:*/
#line 42 "./sat-color-log2.w"

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
printf("~ sat-color-log2 %s %d\n",argv[1],c);

/*:2*/
#line 32 "./sat-color-log2.w"
;
for(t= 0;c> (1<<t);t++);
/*3:*/
#line 58 "./sat-color-log2.w"

for(i= 0;i<t;i++)if(((c-1)&(1<<i))==0){
for(v= g->vertices;v<g->vertices+g->n;v++){
printf("~%s.%d",v->name,t-i);
for(k= i+1;k<t;k++)if((c-1)&(1<<k))
printf(" ~%s.%d",v->name,t-k);
printf("\n");
}
}

/*:3*/
#line 34 "./sat-color-log2.w"
;
for(v= g->vertices;v<g->vertices+g->n;v++)for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u<v)
/*4:*/
#line 68 "./sat-color-log2.w"

{
for(k= 0;k<c;k++){
for(i= 0;i<t;i++)
if(k&(1<<i))
printf(" ~%s.%d ~%s.%d",u->name,t-i,v->name,t-i);
else printf(" %s.%d %s.%d",u->name,t-i,v->name,t-i);
printf("\n");
}
}

/*:4*/
#line 38 "./sat-color-log2.w"
;
}
}

/*:1*/
