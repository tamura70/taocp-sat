/*1:*/
#line 16 "./sat-color.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
#line 4 "./sat-color-snark2.ch"
int c;
int n;
char buf[20];
#line 22 "./sat-color.w"
main(int argc,char*argv[]){
register int i,j,k;
register Arc*a;
register Graph*g;
register Vertex*v;
/*2:*/
#line 25 "./sat-color-snark2.ch"

if(argc!=2||sscanf(argv[1],"%d",&n)!=1){
fprintf(stderr,"Usage: %s n\n",argv[0]);
exit(-1);
}
sprintf(buf,"fsnarkline%d.gb",n);
g= restore_graph(buf);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",buf);
exit(-2);
}
c= 3;
printf("~ sat-color-snark2 %d\n",n);
printf("b1.1\n");
printf("c1.2\n");
printf("d1.3\n");
#line 47 "./sat-color.w"

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

#line 45 "./sat-color-snark2.ch"
/*:4*//*5:*/
#line 48 "./sat-color-snark2.ch"

for(v= g->vertices;v<g->vertices+g->n;v++){
printf("~%s.1 ~%s.2\n",v->name,v->name);
printf("~%s.2 ~%s.3\n",v->name,v->name);
printf("~%s.3 ~%s.1\n",v->name,v->name);
}

/*:5*/
#line 29 "./sat-color.w"
;
}

#line 25 "./sat-color-snark2.ch"
/*:1*/
