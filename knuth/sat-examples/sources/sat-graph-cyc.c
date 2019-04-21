#define maxn 100 \

#define elig u.I \

#define rrank y.I \

/*1:*/
#line 16 "./graph-cyc.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#line 16 "./sat-graph-cyc.ch"
#include "gb_save.h"
#include "gb_flip.h"
int seed;
#line 21 "./graph-cyc.w"
int kk;
Vertex*vv[maxn];
Arc*aa[maxn];
long count;
main(int argc,char*argv[]){
register int i,j,k;
register Graph*g;
register Vertex*u,*v;
register Arc*a,*b;
Vertex*v0;
#line 23 "./sat-graph-cyc.ch"
/*2:*/
#line 31 "./sat-graph-cyc.ch"

if(argc!=4||sscanf(argv[2],"%d",&kk)!=1||sscanf(argv[3],"%d",&seed)!=1){
fprintf(stderr,"Usage: %s foo.gb k seed\n",
#line 42 "./graph-cyc.w"
argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I couldn't reconstruct graph %s!\n",
argv[1]);
exit(-2);
}
if(g->n> maxn){
fprintf(stderr,"Recompile me: g->n=%ld, maxn=%d!\n",
g->n,maxn);
exit(-3);
}
if(kk<3){
fprintf(stderr,"The cycle length must be 3 or more, not %d!\n",
kk);
exit(-4);
}

/*:2*/
#line 23 "./sat-graph-cyc.ch"
;
/*6:*/
#line 46 "./sat-graph-cyc.ch"

gb_init_rand(seed);
for(v= g->vertices;v<g->vertices+g->n;v++)v->rrank= gb_next_rand();
printf("~ sat-graph-cyc %s %d %d\n",argv[1],kk,seed);

/*:6*/
#line 24 "./sat-graph-cyc.ch"
;
#line 32 "./graph-cyc.w"
/*5:*/
#line 103 "./graph-cyc.w"

(g->vertices+g->n-1)->elig= 0;

#line 44 "./sat-graph-cyc.ch"
/*:5*/
#line 32 "./graph-cyc.w"
;
for(v0= g->vertices+g->n-1;v0>=g->vertices;v0--)
/*3:*/
#line 64 "./graph-cyc.w"

{
vv[0]= v0;
for(v= g->vertices;v<v0;v++)v->elig= 0;
for(a= v->arcs;a;a= a->next)if(a->tip<v0)break;
if(a==0)continue;
aa[1]= a,k= 1;
try_again:if(k==1)aa[1]->tip->elig= 1;
for(a= aa[k]->next;a;a= a->next)if(a->tip<v0)break;
tryit:if(a==0)goto backtrack;
aa[k]= a,vv[k]= v= a->tip;
for(j= 0;vv[j]!=v;j++);
if(j<k)goto try_again;
k++;
new_level:if(k==kk)/*4:*/
#line 86 "./graph-cyc.w"

{
if(v->elig){
#line 39 "./sat-graph-cyc.ch"
/*7:*/
#line 51 "./sat-graph-cyc.ch"

vv[kk]= vv[0],vv[kk+1]= vv[1];
for(i= 1,j= 2;j<=kk;j++)if(vv[j]->rrank> vv[i]->rrank)i= j;
if(vv[i+1]->rrank> vv[i-1]->rrank){
for(j= i;j<kk;j++)
printf(" %s%s.%s",
(j-i)&1?"":"~",
vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
vv[j]> vv[j+1]?vv[j]->name:vv[j+1]->name);
for(j= 0;j<i;j++)
printf(" %s%s.%s",
(j-i)&1?"":"~",
vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
vv[j]> vv[j+1]?vv[j]->name:vv[j+1]->name);
}else{
for(j= i;j<kk;j++)
printf(" %s%s.%s",
(j-i)&1?"~":"",
vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
vv[j]> vv[j+1]?vv[j]->name:vv[j+1]->name);
for(j= 0;j<i;j++)
printf(" %s%s.%s",
(j-i)&1?"~":"",
vv[j]<vv[j+1]?vv[j]->name:vv[j+1]->name,
vv[j]> vv[j+1]?vv[j]->name:vv[j+1]->name);
}

/*:7*/
#line 39 "./sat-graph-cyc.ch"
;
#line 91 "./graph-cyc.w"
printf("\n");
count++;
}
goto backtrack;
}

/*:4*/
#line 78 "./graph-cyc.w"
;
for(a= vv[k-1]->arcs;a;a= a->next)if(a->tip<v0)break;
goto tryit;
backtrack:if(--k)goto try_again;
}

/*:3*/
#line 34 "./graph-cyc.w"
;
fprintf(stderr,"Altogether %ld cycles found.\n",
count);
}

#line 31 "./sat-graph-cyc.ch"
/*:1*/
