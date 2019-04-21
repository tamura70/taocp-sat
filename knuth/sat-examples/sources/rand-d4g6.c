#define maxn 100
#define maxe ((maxn*(maxn-1) ) >>1)  \

#define sanity_checking time>=0 \

#define embargo 10 \

/*1:*/
#line 16 "./rand-d4g6.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_flip.h"
int nn;
int seed;
int e;
/*4:*/
#line 83 "./rand-d4g6.w"

typedef struct{
int u,v;
int uinx,vinx;
}edge;

/*:4*/
#line 23 "./rand-d4g6.w"
;
/*3:*/
#line 72 "./rand-d4g6.w"

int adj[maxn][4];
int deg[maxn];
int dg[5][maxn];
int dglen[5];
int dginx[maxn];

/*:3*//*5:*/
#line 94 "./rand-d4g6.w"

edge ee[2*maxn];
int adjinx[maxn][4];

/*:5*//*7:*/
#line 138 "./rand-d4g6.w"

int time;
int wait[maxn][maxn];
int uelig[maxe],velig[maxe];
int elig;

/*:7*//*17:*/
#line 236 "./rand-d4g6.w"

int stamp[maxn];
int curstamp;
int queue[maxn];
int vbose;

/*:17*/
#line 24 "./rand-d4g6.w"
;
/*6:*/
#line 102 "./rand-d4g6.w"

void sanity_fail(char*m,int x,int y){
fprintf(stderr,"%s (%d,%d)!\n",m,x,y);
}

void sanity(void){
register d,j,s,u,v;
for(v= s= 0;v<nn;v++)s+= deg[v];
if(s!=2*e)sanity_fail("bad sum of degs",s,2*e);
for(d= s= 0;d<=4;d++)s+= dglen[d];
if(s!=nn)sanity_fail("bad sum of dglens",s,nn);
for(d= 0;d<=4;d++)for(j= 0;j<dglen[d];j++){
v= dg[d][j];
if(deg[v]!=d)sanity_fail("bad deg",v,d);
if(dginx[v]!=j)sanity_fail("bad dginx",v,j);
}
for(j= 0;j<e;j++){
u= ee[j].u,v= ee[j].v;
if(u!=adj[v][ee[j].uinx])sanity_fail("bad uinx",u,v);
if(v!=adj[u][ee[j].vinx])sanity_fail("bad vinx",u,v);
if(adjinx[u][ee[j].vinx]!=j)sanity_fail("bad adjinx",u,j);
if(adjinx[v][ee[j].uinx]!=j)sanity_fail("bad adjinx",v,j);
}
}

/*:6*//*9:*/
#line 151 "./rand-d4g6.w"

void insert(register int u,register int v){
register int d,j,k,w;
ee[e].u= u,ee[e].v= v;
/*10:*/
#line 161 "./rand-d4g6.w"

d= deg[u],adj[u][d]= v,adjinx[u][d]= e,ee[e].vinx= d,deg[u]= d+1;
j= dginx[u],k= dglen[d];
w= dg[d][k-1],dg[d][j]= w,dginx[w]= j,dglen[d]= k-1;
k= dglen[d+1],dg[d+1][k]= u,dginx[u]= k,dglen[d+1]= k+1;

/*:10*/
#line 155 "./rand-d4g6.w"
;
/*11:*/
#line 169 "./rand-d4g6.w"

d= deg[v],adj[v][d]= u,adjinx[v][d]= e,ee[e].uinx= d,deg[v]= d+1;
j= dginx[v],k= dglen[d];
w= dg[d][k-1],dg[d][j]= w,dginx[w]= j,dglen[d]= k-1;
k= dglen[d+1],dg[d+1][k]= v,dginx[v]= k,dglen[d+1]= k+1;

/*:11*/
#line 156 "./rand-d4g6.w"
;
}

/*:9*//*12:*/
#line 177 "./rand-d4g6.w"

void delete(register int j){
register int d,i,k,u,v,ui,vi,w;
u= ee[j].u,v= ee[j].v,ui= ee[j].uinx,vi= ee[j].vinx;
/*13:*/
#line 186 "./rand-d4g6.w"

d= deg[v];
if(ui!=d-1){
w= adj[v][d-1],i= adjinx[v][d-1],adj[v][ui]= w,adjinx[v][ui]= i;
if(w==ee[i].u)ee[i].uinx= ui;
else ee[i].vinx= ui;
}
deg[v]= d-1,i= dginx[v],k= dglen[d];
w= dg[d][k-1],dg[d][i]= w,dginx[w]= i,dglen[d]= k-1;
k= dglen[d-1],dg[d-1][k]= v,dginx[v]= k,dglen[d-1]= k+1;

/*:13*/
#line 181 "./rand-d4g6.w"
;
/*14:*/
#line 197 "./rand-d4g6.w"

d= deg[u];
if(vi!=d-1){
w= adj[u][d-1],i= adjinx[u][d-1],adj[u][vi]= w,adjinx[u][vi]= i;
if(w==ee[i].u)ee[i].uinx= vi;
else ee[i].vinx= vi;
}
deg[u]= d-1,i= dginx[u],k= dglen[d];
w= dg[d][k-1],dg[d][i]= w,dginx[w]= i,dglen[d]= k-1;
k= dglen[d-1],dg[d-1][k]= u,dginx[u]= k,dglen[d-1]= k+1;

/*:14*/
#line 182 "./rand-d4g6.w"
;
/*15:*/
#line 208 "./rand-d4g6.w"

if(j!=e-1){
u= ee[e-1].u,v= ee[e-1].v,ui= ee[e-1].uinx,vi= ee[e-1].vinx;
ee[j]= ee[e-1];
adjinx[v][ui]= j;
adjinx[u][vi]= j;
}

/*:15*/
#line 183 "./rand-d4g6.w"
;
}

/*:12*/
#line 25 "./rand-d4g6.w"
;
main(int argc,char*argv[]){
register int i,j,k,s,d1,d2,u,v,w,p,t,uu;
/*2:*/
#line 46 "./rand-d4g6.w"

if(argc!=3||sscanf(argv[1],"%d",&nn)!=1
||sscanf(argv[2],"%d",&seed)!=1){
fprintf(stderr,"Usage: %s n seed\n",argv[0]);
exit(-1);
}
if(nn> maxn){
fprintf(stderr,"Recompile me: I don't allow n (%d) to exceed %d!\n",nn,maxn);
exit(-2);
}
gb_init_rand(seed);

/*:2*/
#line 28 "./rand-d4g6.w"
;
/*8:*/
#line 144 "./rand-d4g6.w"

e= 0;
for(v= 0;v<nn;v++)deg[v]= 0,dg[0][v]= v,dginx[v]= v;
dglen[0]= nn;

/*:8*/
#line 29 "./rand-d4g6.w"
;
for(e= 0;e<2*nn;){
if(sanity_checking)sanity();
for(s= 6;s>=0;s--){
for(p= 0,d1= (s> 3?3:s),d2= s-d1;d1>=d2;d1--,d2++)
/*16:*/
#line 220 "./rand-d4g6.w"

if(dglen[d1]&&dglen[d2]){
for(i= dglen[d1]-1;i>=0;i--){
u= dg[d1][i];
/*18:*/
#line 242 "./rand-d4g6.w"

{
register int front,rear,nextfront;
curstamp++;
if(curstamp==0){
fprintf(stderr,"Hey, you better give up!\n");
exit(-666);
}
queue[0]= u,front= 0,rear= 1,stamp[u]= curstamp;
for(k= 0;k<4;k++){
for(nextfront= rear;front<nextfront;front++){
uu= queue[front];
for(t= deg[uu]-1;t>=0;t--){
w= adj[uu][t];
if(stamp[w]!=curstamp)
stamp[w]= curstamp,queue[rear++]= w;
}
}
}
}

/*:18*/
#line 224 "./rand-d4g6.w"
;
for(j= (d1==d2?i-1:dglen[d2]-1);j>=0;j--){
v= dg[d2][j];
if((stamp[v]!=curstamp)&&(time>=wait[u][v]))
uelig[p]= u,velig[p]= v,p++;
}
}
}

/*:16*/
#line 35 "./rand-d4g6.w"
;
if(p)goto progress;
}
/*20:*/
#line 273 "./rand-d4g6.w"

j= gb_unif_rand(e);
if(vbose)
fprintf(stderr,"%d: Deleting %d--%d (%d present)\n",
time,ee[j].u,ee[j].v,e);
delete(j);
wait[ee[j].u][ee[j].v]= wait[ee[j].v][ee[j].u]= time+embargo;

/*:20*/
#line 38 "./rand-d4g6.w"
;
e--;continue;
progress:/*19:*/
#line 263 "./rand-d4g6.w"

j= gb_unif_rand(p);
if(vbose)
fprintf(stderr,"%d: Inserting %d--%d (%d,%d; %d elig)\n",
time,uelig[j],velig[j],deg[uelig[j]],deg[velig[j]],p);
insert(uelig[j],velig[j]);
time++;

/*:19*/
#line 40 "./rand-d4g6.w"
;
e++;
}
/*21:*/
#line 281 "./rand-d4g6.w"

for(j= 0;j<e;j++)
printf("%d %d\n",ee[j].u,ee[j].v);

/*:21*/
#line 43 "./rand-d4g6.w"
;
}

/*:1*/
