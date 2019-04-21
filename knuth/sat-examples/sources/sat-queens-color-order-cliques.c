/*1:*/
#line 6 "./sat-queens-color-order-cliques.w"

#include <stdio.h> 
#include <stdlib.h> 
int n;
int d;
main(int argc,char*argv[]){
register int i,j,k,l;
/*2:*/
#line 17 "./sat-queens-color-order-cliques.w"

if(argc!=3||sscanf(argv[1],"%d",&n)!=1
||sscanf(argv[2],"%d",&d)!=1){
fprintf(stderr,"Usage: %s n d\n",argv[0]);
exit(-1);
}
if(d<n){
fprintf(stderr,"The number of colors (%d) must be at least %d!\n",d,n);
exit(-2);
}
printf("~ sat-queens-color-order-cliques %d %d\n",n,d);

/*:2*/
#line 13 "./sat-queens-color-order-cliques.w"
;
/*3:*/
#line 29 "./sat-queens-color-order-cliques.w"

for(k= 0;k<n;k++){
/*4:*/
#line 39 "./sat-queens-color-order-cliques.w"

{
for(j= 0;j<n;j++)
printf(" %d.%d<%d",
k,j,d-n+1);
printf("\n");
for(j= 0;j<n;j++)
printf(" ~%d.%d<%d",
k,j,n-1);
printf("\n");
}

/*:4*/
#line 31 "./sat-queens-color-order-cliques.w"
;
/*5:*/
#line 51 "./sat-queens-color-order-cliques.w"

{
for(j= 0;j<n;j++)
printf(" %d.%d<%d",
j,k,d-n+1);
printf("\n");
for(j= 0;j<n;j++)
printf(" ~%d.%d<%d",
j,k,n-1);
printf("\n");
}

/*:5*/
#line 32 "./sat-queens-color-order-cliques.w"
;
}
for(k= 1;k<=n+n-3;k++)
/*6:*/
#line 63 "./sat-queens-color-order-cliques.w"

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
}
}

/*:6*/
#line 35 "./sat-queens-color-order-cliques.w"
;
for(k= 2-n;k<=n-2;k++)
/*7:*/
#line 88 "./sat-queens-color-order-cliques.w"

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
}
}

/*:7*/
#line 37 "./sat-queens-color-order-cliques.w"
;

/*:3*/
#line 14 "./sat-queens-color-order-cliques.w"
;
}

/*:1*/
