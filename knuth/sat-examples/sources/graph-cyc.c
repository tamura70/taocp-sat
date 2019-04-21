#define maxn 100 \

#define elig u.I \

/*1:*/
#line 16 "./graph-cyc.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
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
/*2:*/
#line 39 "./graph-cyc.w"

if(argc!=3||sscanf(argv[2],"%d",&kk)!=1){
fprintf(stderr,"Usage: %s foo.gb k\n",
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
#line 31 "./graph-cyc.w"
;
/*5:*/
#line 103 "./graph-cyc.w"

(g->vertices+g->n-1)->elig= 0;

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
for(j= 0;j<kk;j++)printf(" %s",
vv[j]->name);
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

/*:1*/
