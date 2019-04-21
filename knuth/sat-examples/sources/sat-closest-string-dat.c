#define maxn 10000 \

/*1:*/
#line 15 "./sat-closest-string-dat.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_flip.h"
char secret[maxn+1];
int del[maxn];
int m,n,rmin,rmax,s;
main(int argc,char*argv[]){
register int c,i,j,k,o,r;
/*2:*/
#line 32 "./sat-closest-string-dat.w"

if(argc!=6||
sscanf(argv[1],"%d",
&n)!=1||
sscanf(argv[2],"%d",
&m)!=1||
sscanf(argv[3],"%d",
&rmin)!=1||
sscanf(argv[4],"%d",
&rmax)!=1||
sscanf(argv[5],"%d",
&s)!=1){
fprintf(stderr,"Usage: %s n m rmin rmax seed\n",
argv[0]);
exit(-1);
}
if(n==0||n> maxn){
fprintf(stderr,"Oops: n should be between 1 and %d, not %d!\n",
maxn,n);
exit(-2);
}
if(rmin<=0||rmin> rmax||rmax>=n){
fprintf(stderr,"Oops: I assume that 0 < rmin <= rmax < n!\n");
exit(-3);
}
printf("! sat-closest-string-dat %d %d %d %d %d\n",
n,m,rmin,rmax,s);
gb_init_rand(s);

/*:2*/
#line 24 "./sat-closest-string-dat.w"
;
/*3:*/
#line 61 "./sat-closest-string-dat.w"

for(i= 0;i<n;i++)
secret[i]= gb_unif_rand(2)+'0';
printf("! %s\n",
secret);

/*:3*/
#line 25 "./sat-closest-string-dat.w"
;
for(c= o= 0,j= 1;j<=m;j++)/*4:*/
#line 67 "./sat-closest-string-dat.w"

{
r= rmin;
if(r<rmax)r+= gb_unif_rand(rmax-rmin+1);
for(k= 0;k<r;k++){
i= gb_unif_rand(n);
if(del[i]==j)c++;
else if(del[i])o++;
del[i]= j;
}
for(i= 0;i<n;i++)
printf("%c",
del[i]==j?secret[i]^1:secret[i]);
printf(" %d\n",
r);
}

/*:4*/
#line 26 "./sat-closest-string-dat.w"
;
fprintf(stderr,
"OK, I generated %d strings, with %d collisions and %d overlaps.\n",
m,c,o);
}

/*:1*/
