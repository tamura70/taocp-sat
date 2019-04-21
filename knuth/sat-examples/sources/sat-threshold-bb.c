#define nmax 10000 \

#define xbar(k) printf("~x%d",(k) -n+2)  \

/*1:*/
#line 15 "./sat-threshold-bb.w"

#include <stdio.h> 
#include <stdlib.h> 
int n,r;
int count[nmax+nmax];
main(int argc,char*argv[]){
register int i,j,k,jl,jr,t,tl,tr;
/*2:*/
#line 31 "./sat-threshold-bb.w"

if(argc!=3||sscanf(argv[1],"%d",&n)!=1||sscanf(argv[2],"%d",&r)!=1){
fprintf(stderr,"Usage: %s n r\n",argv[0]);
exit(-1);
}
if(n> nmax){
fprintf(stderr,"Recompile me: I'd don't allow n>%d\n",nmax);
exit(-2);
}
if(r<0||r>=n){
fprintf(stderr,"Eh? r should be between 0 and n-1!\n");
exit(-2);
}
printf("~ sat-threshold-bb %d %d\n",n,r);

/*:2*/
#line 22 "./sat-threshold-bb.w"
;
if(r==0)/*6:*/
#line 104 "./sat-threshold-bb.w"

{
for(i= 1;i<=n;i++){
xbar(n-2+i);
printf("\n");
}
}

/*:6*/
#line 23 "./sat-threshold-bb.w"

else{
/*3:*/
#line 50 "./sat-threshold-bb.w"

for(k= n+n-2;k>=n-1;k--)count[k]= 1;
for(;k>=0;k--)
count[k]= count[k+k+1]+count[k+k+2];
if(count[0]!=n)
fprintf(stderr,"I'm totally confused.\n");

/*:3*/
#line 25 "./sat-threshold-bb.w"
;
for(i= n-2;i;i--)/*4:*/
#line 64 "./sat-threshold-bb.w"

{
t= count[i],tl= count[i+i+1],tr= count[i+i+2];
if(t> r+1)t= r+1;
if(tl> r)tl= r;
if(tr> r)tr= r;
for(jl= 0;jl<=tl;jl++)for(jr= 0;jr<=tr;jr++)
if((jl+jr<=t)&&(jl+jr)> 0){
if(jl){
if(i+i+1>=n-1)xbar(i+i+1);
else printf("~B%d.%d",i+i+2,jl);
}
if(jr){
printf(" ");
if(i+i+2>=n-1)xbar(i+i+2);
else printf("~B%d.%d",i+i+3,jr);
}
if(jl+jr<=r)printf(" B%d.%d\n",i+1,jl+jr);
else printf("\n");
}
}

/*:4*/
#line 26 "./sat-threshold-bb.w"
;
/*5:*/
#line 89 "./sat-threshold-bb.w"

tl= count[1],tr= count[2];
if(tl> r)tl= r;
for(jl= 1;jl<=tl;jl++){
jr= r+1-jl;
if(jr<=tr){
if(1>=n-1)xbar(1);
else printf("~B2.%d",jl);
printf(" ");
if(2>=n-1)xbar(2);
else printf("~B3.%d",jr);
printf("\n");
}
}

/*:5*/
#line 27 "./sat-threshold-bb.w"
;
}
}

/*:1*/
