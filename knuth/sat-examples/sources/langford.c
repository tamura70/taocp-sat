/*1:*/
#line 10 "./langford.w"

#include <stdio.h> 
#include <stdlib.h> 
int n;
main(int argc,char*argv[])
{
register int i,j,k,nn;
if(argc!=2||sscanf(argv[1],"%d",&n)!=1){
fprintf(stderr,"Usage: %s n\n",argv[0]);
exit(-1);
}
nn= n+n;
/*2:*/
#line 31 "./langford.w"

for(j= 1;j<=n;j++)printf("d%d ",j);
for(j= 1;j<=nn;j++)printf("s%d ",j);
printf("\n");

/*:2*/
#line 22 "./langford.w"
;
for(i= 1;i<=n;i++)for(j= 1;;j++){
k= i+j+1;
if(k> nn)break;
if(i==n-((n&1)==0)&&j> n/2)break;
printf("d%d s%d s%d\n",i,j,k);
}
}

/*:1*/
