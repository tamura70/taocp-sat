/*1:*/
#line 26 "./sat-color-log.w"

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
#line 47 "./sat-color-log.w"

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
printf("~ sat-color-log %s %d\n",argv[1],c);

/*:2*/
#line 37 "./sat-color-log.w"
;
for(t= 0;c> (1<<t);t++);
/*3:*/
#line 63 "./sat-color-log.w"

for(i= 0;i<t;i++)if(((c-1)&(1<<i))==0){
for(v= g->vertices;v<g->vertices+g->n;v++){
printf("~%s.%d",v->name,t-i);
for(k= i+1;k<t;k++)if((c-1)&(1<<k))
printf(" ~%s.%d",v->name,t-k);
printf("\n");
}
}

/*:3*/
#line 39 "./sat-color-log.w"
;
for(v= g->vertices;v<g->vertices+g->n;v++)for(a= v->arcs;a;a= a->next){
u= a->tip;
if(u<v)
/*4:*/
#line 73 "./sat-color-log.w"

{
for(k= 1;k<=t;k++){
printf("~%s^%s%d %s.%d %s.%d\n",u->name,v->name,k,u->name,k,v->name,k);


printf("~%s^%s%d ~%s.%d ~%s.%d\n",u->name,v->name,k,u->name,k,v->name,k);
}
for(k= 1;k<=t;k++)
printf(" %s^%s%d",u->name,v->name,k);
printf("\n");
}

/*:4*/
#line 43 "./sat-color-log.w"
;
}
}

/*:1*/
