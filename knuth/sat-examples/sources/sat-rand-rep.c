/*1:*/
#line 19 "./sat-rand-rep.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_flip.h"
int k,m,n,seed;
main(int argc,char*argv[]){
register int i,j,t,ii,kk,nn;
/*2:*/
#line 32 "./sat-rand-rep.w"

if(argc!=5||sscanf(argv[1],"%d",&k)!=1||
sscanf(argv[2],"%d",&m)!=1||
sscanf(argv[3],"%d",&n)!=1||
sscanf(argv[4],"%d",&seed)!=1){
fprintf(stderr,"Usage: %s k m n seed\n",argv[0]);
exit(-1);
}
if(k<=0){
fprintf(stderr,"k must be positive!\n");
exit(-2);
}
if(m<=0){
fprintf(stderr,"m must be positive!\n");
exit(-3);
}
if(n<=0||n>=100000000){
fprintf(stderr,"n must be between 1 and 99999999, inclusive!\n");
exit(-4);
}
if(k> n){
fprintf(stderr,"k mustn't exceed n!\n");
exit(-5);
}
gb_init_rand(seed);

/*:2*/
#line 26 "./sat-rand-rep.w"
;
printf("~ sat-rand-rep %d %d %d %d\n",k,m,n,seed);
for(j= 0;j<m;j++)
/*3:*/
#line 61 "./sat-rand-rep.w"

{
for(kk= k,nn= n;kk;kk--,nn= ii){
/*4:*/
#line 70 "./sat-rand-rep.w"

for(ii= i= 0;i<kk;i++){
t= i+gb_unif_rand(nn-i);
if(t> ii)ii= t;
}


/*:4*/
#line 64 "./sat-rand-rep.w"
;
printf(" %s%d",gb_next_rand()&1?"~":"",ii);
}
printf("\n");
}

/*:3*/
#line 29 "./sat-rand-rep.w"
;
}

/*:1*/
