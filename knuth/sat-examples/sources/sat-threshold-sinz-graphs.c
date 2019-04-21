#define xbar(k) printf("~%s.%d",(g->vertices+k-1) ->name,kk)  \

/*1:*/
#line 10 "./sat-threshold-sinz.w"

#include <stdio.h> 
#include <stdlib.h> 
#line 11 "./sat-threshold-sinz-graphs.ch"
#include "gb_graph.h"
#include "gb_save.h"
int n,r,kk;
#line 14 "./sat-threshold-sinz.w"
main(int argc,char*argv[]){
#line 18 "./sat-threshold-sinz-graphs.ch"
register int i,j,k;
Graph*g;
#line 16 "./sat-threshold-sinz.w"
/*2:*/
#line 21 "./sat-threshold-sinz.w"

#line 27 "./sat-threshold-sinz-graphs.ch"
if(argc!=5||sscanf(argv[1],"%d",&n)!=1||sscanf(argv[2],"%d",&r)!=1||
sscanf(argv[4],"%d",&kk)!=1){
fprintf(stderr,"Usage: %s n r foo.gb k\n",argv[0]);
exit(-1);
}
g= restore_graph(argv[3]);
if(!g){
fprintf(stderr,"I can't input the graph `%s'!\n",argv[3]);
exit(-2);
}
if(g->n!=n)
fprintf(stderr,"Warning: The graph has %ld vertices, not %d!\n",g->n,n);
#line 26 "./sat-threshold-sinz.w"
if(r<0||r>=n){
fprintf(stderr,"Eh? r should be between 0 and n-1!\n");
exit(-2);
}
printf("~ sat-threshold-sinz %d %d\n",n,r);

/*:2*/
#line 16 "./sat-threshold-sinz.w"
;
for(j= 1;j<=r;j++)/*3:*/
#line 32 "./sat-threshold-sinz.w"

for(i= 1;i<n-r;i++)
printf("~S%d.%d S%d.%d\n",i,j,i+1,j);

#line 43 "./sat-threshold-sinz-graphs.ch"
/*:3*/
#line 17 "./sat-threshold-sinz.w"
;
for(j= 0;j<=r;j++)/*4:*/
#line 38 "./sat-threshold-sinz.w"

for(i= 1;i<=n-r;i++){
xbar(i+j);
if(j)printf(" ~S%d.%d",i,j);
if(j<r)printf(" S%d.%d",i,j+1);
printf("\n");
}

/*:4*/
#line 18 "./sat-threshold-sinz.w"
;
}

/*:1*/
