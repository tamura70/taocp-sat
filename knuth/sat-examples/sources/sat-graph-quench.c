#define nmax 256 \

#define stamp u.I \

/*1:*/
#line 36 "./sat-graph-quench.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
main(int argc,char*argv[]){
register int i,j,k,t,n;
register Arc*a;
register Graph*g;
register Vertex*v,*w;
/*2:*/
#line 53 "./sat-graph-quench.w"

if(argc!=2){
fprintf(stderr,"Usage: %s foo.gb\n",argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",argv[1]);
exit(-2);
}
n= g->n;
if(n> nmax){
fprintf(stderr,"Sorry, that graph has too many vertices (%d>%d)!\n",
n,nmax);
exit(-3);
}
printf("~ sat-graph-quench %s\n",argv[1]);

/*:2*/
#line 46 "./sat-graph-quench.w"
;
/*3:*/
#line 78 "./sat-graph-quench.w"

for(v= g->vertices;v<g->vertices+n;v++)v->stamp= 0;
for(v= g->vertices,j= 1;v<g->vertices+n;v++,j++){
for(a= v->arcs;a;a= a->next)if(a->tip> v)
a->tip->stamp= j;
for(w= v+1;w<g->vertices+n;w++)if(w->stamp!=j)
printf("~00%02x%02x\n",
(unsigned int)(v-g->vertices),(unsigned int)(w-g->vertices));
}

/*:3*/
#line 47 "./sat-graph-quench.w"
;
/*4:*/
#line 88 "./sat-graph-quench.w"

for(t= 0;t<n-1;t++){
for(k= 1;k<n-t;k++)printf(" %02xQ%02x",
t,k-1);
for(k= 1;k<n-t-2;k++)printf(" %02xS%02x",
t,k-1);
printf("\n");
}

/*:4*/
#line 48 "./sat-graph-quench.w"
;
/*5:*/
#line 97 "./sat-graph-quench.w"

for(t= 0;t<n-1;t++){
for(k= 1;k<n-t;k++)printf("~%02xQ%02x %02x%02x%02x\n",
t,k-1,t,k-1,k);
for(k= 1;k<n-t-2;k++)printf("~%02xS%02x %02x%02x%02x\n",
t,k-1,t,k-1,k+2);
}

/*:5*/
#line 49 "./sat-graph-quench.w"
;
/*6:*/
#line 105 "./sat-graph-quench.w"

for(t= 0;t<n-1;t++){
for(k= 1;k<n-t;k++)
for(i= 1;i<n-t;i++)for(j= i+1;j<n-t;j++)
printf("~%02xQ%02x ~%02x%02x%02x %02x%02x%02x\n",
t,k-1,t+1,i-1,j-1,t,i<k?i-1:i,j<k?j-1:j);
for(k= 1;k<n-t-2;k++)
for(i= 1;i<n-t;i++)for(j= i+1;j<n-t;j++){
register iprev= (i==k?i+2:i<k+3?i-1:i),
jprev= (j==k?j+2:j<k+3?j-1:j);
printf("~%02xS%02x ~%02x%02x%02x %02x%02x%02x\n",
t,k-1,t+1,i-1,j-1,t,iprev<jprev?iprev:jprev,iprev<jprev?jprev:iprev);
}
}

/*:6*/
#line 50 "./sat-graph-quench.w"
;
}

/*:1*/
