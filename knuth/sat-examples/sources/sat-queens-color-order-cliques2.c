#define maxd 100 \

/*1:*/
#line 12 "./sat-queens-color-order-cliques2.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_flip.h"
int n;
int d;
int seed;
int perm[maxd];
main(int argc,char*argv[]){
register int i,j,k,l;
/*2:*/
#line 27 "./sat-queens-color-order-cliques2.w"

if(argc!=4||sscanf(argv[1],"%d",&n)!=1
||sscanf(argv[2],"%d",&d)!=1
||sscanf(argv[3],"%d",&seed)!=1){
fprintf(stderr,"Usage: %s n d seed\n",argv[0]);
exit(-1);
}
if(d<n){
fprintf(stderr,"The number of colors (%d) must be at least %d!\n",d,n);
exit(-2);
}
if(d> maxd){
fprintf(stderr,"The number of colors (%d) must be at most %d!\n",d,maxd);
exit(-2);
}
gb_init_rand(seed);
printf("~ sat-queens-color-order-cliques2 %d %d %d\n",n,d,seed);

/*:2*/
#line 22 "./sat-queens-color-order-cliques2.w"
;
/*3:*/
#line 45 "./sat-queens-color-order-cliques2.w"

for(i= 1;i<d;i++){
j= gb_unif_rand(i+1);
perm[i]= perm[j];
perm[j]= i;
}
printf("~");
for(i= 0;i<d;i++)printf(" %d",perm[i]);
printf("\n");

/*:3*/
#line 23 "./sat-queens-color-order-cliques2.w"
;
/*4:*/
#line 55 "./sat-queens-color-order-cliques2.w"

/*5:*/
#line 66 "./sat-queens-color-order-cliques2.w"

for(i= 0;i<n;i++)for(j= 0;j<n;j++){
for(k= 0;k<d;k++){
if(k> 0&&k<d-1)printf("~%d.%d!%d %d.%d!%d\n",
i,j,perm[k],i,j,perm[k+1]);
if(perm[k]+1<d){
if(k+1<d)printf("~%d.%d!%d",
i,j,perm[k+1]);
if(k)printf(" %d.%d!%d",
i,j,perm[k]);
printf(" %d.%d<%d\n",
i,j,perm[k]+1);
}
if(perm[k]){
if(k+1<d)printf("~%d.%d!%d",
i,j,perm[k+1]);
if(k)printf(" %d.%d!%d",
i,j,perm[k]);
printf(" ~%d.%d<%d\n",
i,j,perm[k]);
}
if(k+1<d){
if(perm[k]+1<d)
printf("~%d.%d<%d",
i,j,perm[k]+1);
if(perm[k])
printf(" %d.%d<%d",
i,j,perm[k]);
printf(" %d.%d!%d\n",
i,j,perm[k+1]);
}
if(k){
if(perm[k]+1<d)
printf("~%d.%d<%d",
i,j,perm[k]+1);
if(perm[k])
printf(" %d.%d<%d",
i,j,perm[k]);
printf(" ~%d.%d!%d\n",
i,j,perm[k]);
}
}
}

/*:5*/
#line 56 "./sat-queens-color-order-cliques2.w"
;
for(k= 0;k<n;k++){
/*6:*/
#line 110 "./sat-queens-color-order-cliques2.w"

{
for(j= 0;j<n;j++)
printf(" %d.%d<%d",
k,j,d-n+1);
printf("\n");
for(j= 0;j<n;j++)
printf(" ~%d.%d<%d",
k,j,n-1);
printf("\n");
for(j= 0;j<n;j++)
printf(" %d.%d!%d",
k,j,perm[d-n+1]);
printf("\n");
for(j= 0;j<n;j++)
printf(" ~%d.%d!%d",
k,j,perm[n-1]);
printf("\n");
}

/*:6*/
#line 58 "./sat-queens-color-order-cliques2.w"
;
/*7:*/
#line 130 "./sat-queens-color-order-cliques2.w"

{
for(j= 0;j<n;j++)
printf(" %d.%d<%d",
j,k,d-n+1);
printf("\n");
for(j= 0;j<n;j++)
printf(" ~%d.%d<%d",
j,k,n-1);
printf("\n");
for(j= 0;j<n;j++)
printf(" %d.%d!%d",
j,k,perm[d-n+1]);
printf("\n");
for(j= 0;j<n;j++)
printf(" ~%d.%d!%d",
j,k,perm[n-1]);
printf("\n");
}

/*:7*/
#line 59 "./sat-queens-color-order-cliques2.w"
;
}
for(k= 1;k<=n+n-3;k++)
/*8:*/
#line 150 "./sat-queens-color-order-cliques2.w"

{
if(k<n){
l= k+1;
for(i= 0;i<=k;i++)
printf(" %d.%d<%d",
i,k-i,d-l+1);
printf("\n");
for(i= 0;i<=k;i++)
printf(" ~%d.%d<%d",
i,k-i,l-1);
printf("\n");
for(i= 0;i<=k;i++)
printf(" %d.%d!%d",
i,k-i,perm[d-l+1]);
printf("\n");
for(i= 0;i<=k;i++)
printf(" ~%d.%d!%d",
i,k-i,perm[l-1]);
printf("\n");
}else{
l= n+n-1-k;
for(i= n-l;i<n;i++)
printf(" %d.%d<%d",
i,k-i,d-l+1);
printf("\n");
for(i= n-l;i<n;i++)
printf(" ~%d.%d<%d",
i,k-i,l-1);
printf("\n");
for(i= n-l;i<n;i++)
printf(" %d.%d!%d",
i,k-i,perm[d-l+1]);
printf("\n");
for(i= n-l;i<n;i++)
printf(" ~%d.%d!%d",
i,k-i,perm[l-1]);
printf("\n");
}
}

/*:8*/
#line 62 "./sat-queens-color-order-cliques2.w"
;
for(k= 2-n;k<=n-2;k++)
/*9:*/
#line 191 "./sat-queens-color-order-cliques2.w"

{
if(k> 0){
l= n-k;
for(i= k;i<n;i++)
printf(" %d.%d<%d",
i,i-k,d-l+1);
printf("\n");
for(i= k;i<n;i++)
printf(" ~%d.%d<%d",
i,i-k,l-1);
printf("\n");
for(i= k;i<n;i++)
printf(" %d.%d!%d",
i,i-k,perm[d-l+1]);
printf("\n");
for(i= k;i<n;i++)
printf(" ~%d.%d!%d",
i,i-k,perm[l-1]);
printf("\n");
}else{
l= n+k;
for(i= 0;i<n+k;i++)
printf(" %d.%d<%d",
i,i-k,d-l+1);
printf("\n");
for(i= 0;i<n+k;i++)
printf(" ~%d.%d<%d",
i,i-k,l-1);
printf("\n");
for(i= 0;i<n+k;i++)
printf(" %d.%d!%d",
i,i-k,perm[d-l+1]);
printf("\n");
for(i= 0;i<n+k;i++)
printf(" ~%d.%d!%d",
i,i-k,perm[l-1]);
printf("\n");
}
}

/*:9*/
#line 64 "./sat-queens-color-order-cliques2.w"
;

/*:4*/
#line 24 "./sat-queens-color-order-cliques2.w"
;
}

/*:1*/
