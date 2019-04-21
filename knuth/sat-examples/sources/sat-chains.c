#define maxn 6
#define maxk 36 \

#define e(t) ((t) <=9?'0'+t:'a'+t-10)  \

#define bit_h(i) (int) ((x[i]>>((1<<n) -1-h) ) &1)  \

/*1:*/
#line 37 "./sat-chains.w"

#include <stdio.h> 
#include <stdlib.h> 
int n,r;
unsigned long long t[maxk];
unsigned long long x[maxn+1];
/*8:*/
#line 127 "./sat-chains.w"

void printX(char*s,int k,int t){
register int i;
if(k> n){
printf(" %s%c",s,e(k));
for(i= 1;i<=n;i++)printf("%d",(t>>(n-i))&1);
}
}

/*:8*/
#line 43 "./sat-chains.w"
;
main(int argc,char*argv[]){
register int b,bb,bbb,h,i,j,k,m;
register unsigned long long mask;
/*2:*/
#line 52 "./sat-chains.w"

if(argc<4||sscanf(argv[1],"%d",&n)!=1||sscanf(argv[2],"%d",&r)!=1){
fprintf(stderr,"Usage: %s n r t1 ... tm\n",argv[0]);
exit(-1);
}
if(n<2||n> maxn){
fprintf(stderr,"n should be between 2 and %d, not %d!\n",maxn,n);
exit(-2);
}
if(n+r> maxk){
fprintf(stderr,"n+r should be at most %d, not %d!\n",maxk,n+r);
exit(-3);
}
mask= (n==6?-1:(1LL<<(1<<n))-1);
x[1]= mask>>(1<<(n-1));
for(i= 2;i<=n;i++)
x[i]= x[i-1]^(x[i-1]<<(1<<(n-i)));
m= argc-3;
if(m> r){
fprintf(stderr,"the number of outputs should be at most r, not %d!\n",m);
exit(-4);
}
for(i= 1;i<=m;i++){
if(sscanf(argv[2+i],"%llx",&t[i])!=1){
fprintf(stderr,"I couldn't scan truth table t%d!\n",i);
exit(-5);
}
if(n<6&&(t[i]>>(1<<n))){
fprintf(stderr,"Truth table t%d (%llx) has too many bits!\n",i,t[i]);
exit(-6);
}
if(t[i]>>((1<<n)-1))t[i]= (~t[i])&mask;
}
printf("~ sat-chains %d %d",n,r);
for(i= 1;i<=m;i++)printf(" %llx",t[i]);
printf("\n");

/*:2*/
#line 47 "./sat-chains.w"
;
for(k= n+1;k<=n+r;k++)/*3:*/
#line 89 "./sat-chains.w"

{
/*4:*/
#line 101 "./sat-chains.w"

printf("F%c01 F%c10 F%c11\n",e(k),e(k),e(k));
printf("F%c01 ~F%c10 ~F%c11\n",e(k),e(k),e(k));
printf("~F%c01 F%c10 ~F%c11\n",e(k),e(k),e(k));

/*:4*/
#line 91 "./sat-chains.w"
;
/*5:*/
#line 106 "./sat-chains.w"

for(i= 1;i<k;i++)for(j= i+1;j<k;j++)printf(" K%c%c%c",e(k),e(j),e(i));
printf("\n");

/*:5*/
#line 92 "./sat-chains.w"
;
/*6:*/
#line 110 "./sat-chains.w"

for(i= 1;i<=m;i++)printf(" Z%c%c",e(i),e(k));
for(j= k+1;j<=n+r;j++)for(i= 1;i<k;i++)printf(" K%c%c%c",e(j),e(k),e(i));
for(j= k+1;j<=n+r;j++)for(i= k+1;i<j;i++)printf(" K%c%c%c",e(j),e(i),e(k));
printf("\n");

/*:6*/
#line 93 "./sat-chains.w"
;
/*7:*/
#line 121 "./sat-chains.w"

for(i= 1;i<k;i++)for(j= i+1;j<k;j++)for(h= k+1;h<=n+r;h++){
printf("~K%c%c%c ~K%c%c%c\n",e(k),e(j),e(i),e(h),e(k),e(j));
printf("~K%c%c%c ~K%c%c%c\n",e(k),e(j),e(i),e(h),e(k),e(i));
}

/*:7*/
#line 94 "./sat-chains.w"
;
for(i= 1;i<k;i++)for(j= i+1;j<k;j++)
/*9:*/
#line 138 "./sat-chains.w"

{
for(h= 1;h<(1<<n);h++){
for(b= 0;b<=1;b++)for(bb= 0;bb<=1;bb++){
if(j<=n&&bit_h(j)!=b)continue;
if(i<=n&&bit_h(i)!=bb)continue;
if(b+bb==0){
printf("~K%c%c%c",e(k),e(j),e(i));
printX("X",j,h);
printX("X",i,h);
printX("~X",k,h);
printf("\n");
}else for(bbb= 0;bbb<=1;bbb++){
printf("~K%c%c%c",e(k),e(j),e(i));
if(b)printX("~X",j,h);else printX("X",j,h);
if(bb)printX("~X",i,h);else printX("X",i,h);
if(bbb)printX("~X",k,h);else printX("X",k,h);
printf(" %sF%c%d%d\n",bbb?"":"~",e(k),b,bb);
}
}
}
}

/*:9*/
#line 96 "./sat-chains.w"
;
}

/*:3*/
#line 48 "./sat-chains.w"
;
for(i= 1;i<=m;i++)/*10:*/
#line 161 "./sat-chains.w"

{
/*11:*/
#line 168 "./sat-chains.w"

for(k= n+1;k<=n+r;k++)printf(" Z%c%c",e(i),e(k));
printf("\n");

/*:11*/
#line 163 "./sat-chains.w"
;
for(k= n+1;k<=n+r;k++)
/*12:*/
#line 172 "./sat-chains.w"

{
for(h= 1;h<(1<<n);h++){
printf("~Z%c%c",e(i),e(k));
if(t[i]&(1LL<<((1<<n)-1-h)))printX("X",k,h);
else printX("~X",k,h);
printf("\n");
}
}

/*:12*/
#line 165 "./sat-chains.w"
;
}

/*:10*/
#line 49 "./sat-chains.w"
;
}

/*:1*/
