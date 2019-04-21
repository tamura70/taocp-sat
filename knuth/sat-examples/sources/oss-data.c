#define maxn '~'-'0' \

/*1:*/
#line 27 "./oss-data.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_flip.h" 
int n,s,r,seed;
float p;
int w[maxn][maxn];
main(int argc,char*argv[]){
register int i,j,ii,jj,del,max_take,rep;
/*2:*/
#line 42 "./oss-data.w"

if(argc!=6||
sscanf(argv[1],"%d",
&n)!=1||
sscanf(argv[2],"%d",
&s)!=1||
sscanf(argv[3],"%g",
&p)!=1||
sscanf(argv[4],"%d",
&r)!=1||
sscanf(argv[5],"%d",
&seed)!=1){
fprintf(stderr,"Usage: %s n scale prob reps seed\n",
argv[0]);
exit(-1);
}
if(p<0||p>=1.0){
fprintf(stderr,"The probability must be between 0.0 and 1.0, not %.2g!\n",
p);
exit(-2);
}
gb_init_rand(seed);
printf("~ oss-data %d %d %g %d %d\n",
n,s,p,r,seed);

/*:2*/
#line 36 "./oss-data.w"
;
/*3:*/
#line 67 "./oss-data.w"

del= s/n;
for(i= 0;i<n;i++)for(j= 0;j<n;j++)w[i][j]= del;
del= s-n*del;
for(i= 0;i<n;i++)for(j= 0;j<del;j++)
w[i][(i+j)%n]++;

/*:3*/
#line 37 "./oss-data.w"
;
for(rep= 0;rep<r;rep++)/*4:*/
#line 74 "./oss-data.w"

{
while(1){
i= gb_unif_rand(n);
ii= gb_unif_rand(n);
if(i!=ii)break;
}
while(1){
j= gb_unif_rand(n);
jj= gb_unif_rand(n);
if(j!=jj)break;
}
del= (w[i][j]<=w[ii][jj]?w[i][j]:w[ii][jj]);
max_take= (1-p)*(float)del;
if(max_take)del-= gb_unif_rand(max_take);
w[i][j]-= del;
w[ii][j]+= del;
w[i][jj]+= del;
w[ii][jj]-= del;
}

/*:4*/
#line 38 "./oss-data.w"
;
/*5:*/
#line 95 "./oss-data.w"

for(i= 0;i<n;i++){
for(j= 0;j<n;j++)printf(" %d",
w[i][j]);
printf("\n");
}

/*:5*/
#line 39 "./oss-data.w"
;
}

/*:1*/
