#define xbar(k) printf("~x%d",k)  \

/*1:*/
#line 10 "./sat-threshold-sinz.w"

#include <stdio.h> 
#include <stdlib.h> 
int n,r;
main(int argc,char*argv[]){
register int i,j,k;
/*2:*/
#line 21 "./sat-threshold-sinz.w"

if(argc!=3||sscanf(argv[1],"%d",&n)!=1||sscanf(argv[2],"%d",&r)!=1){
fprintf(stderr,"Usage: %s n r\n",argv[0]);
exit(-1);
}
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
