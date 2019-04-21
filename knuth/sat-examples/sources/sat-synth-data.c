#define M 4
#define N 20
#define tmax 5
#define imax 1000
#define O "%" \

/*1:*/
#line 36 "./sat-synth-data.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_flip.h"
int term[M][tmax+1]= {
{-2,-3,-10,0},
{-6,-10,-12,0},
{8,-13,-15,0},
{-8,10,-12,0}};
int seed;
int t;
char x[N+1];
unsigned int randbits;
main(int argc,char*argv[]){
register int a,b,i,j,k;
/*2:*/
#line 59 "./sat-synth-data.w"

if(argc!=3||sscanf(argv[1],""O"d",&t)!=1||
sscanf(argv[2],""O"d",&seed)!=1){
fprintf(stderr,"Usage: "O"s t seed\n",argv[0]);
exit(-1);
}

/*:2*/
#line 51 "./sat-synth-data.w"
;
/*3:*/
#line 66 "./sat-synth-data.w"

gb_init_rand(seed);
for(j= 1;j<=N;j++)x[j]= gb_next_rand()&1;
randbits= 1;

/*:3*/
#line 52 "./sat-synth-data.w"
;
for(i= 0;i<imax;i++){
/*4:*/
#line 71 "./sat-synth-data.w"

for(j= 1;j<=N;j++)printf(""O"d",x[j]);
for(a= 0,j= 0;j<M;j++){
for(b= 1,k= 0;term[j][k];k++)
b&= (term[j][k]> 0?x[term[j][k]]:1-x[-term[j][k]]);
a|= b;
}
printf(":"O"d\n",a);

/*:4*/
#line 54 "./sat-synth-data.w"
;
/*5:*/
#line 80 "./sat-synth-data.w"

for(k= 0;k==0;){
for(j= 1;j<=N;j++){
if(randbits==1){
randbits= gb_next_rand();
for(k= 1;k<t;k++)randbits&= gb_next_rand();
randbits|= 0x80000000;
}
k|= randbits&1;
x[j]^= randbits&1;
randbits>>= 1;
}
}

/*:5*/
#line 55 "./sat-synth-data.w"
;
}
}

/*:1*/
