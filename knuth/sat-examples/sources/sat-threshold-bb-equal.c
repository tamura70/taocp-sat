#define nmax 10000 \

#define xbar(k) printf("~x%d",(k) -n+2)  \

#define x(k) printf("x%d",(k) -n+2)  \

/*1:*/
#line 15 "./sat-threshold-bb-equal.w"

#include <stdio.h> 
#include <stdlib.h> 
int n,r;
int count[nmax+nmax];
main(int argc,char*argv[]){
register int i,j,k,jl,jr,t,tl,tr;
/*2:*/
#line 35 "./sat-threshold-bb-equal.w"

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
printf("~ sat-threshold-bb-equal %d %d\n",n,r);

/*:2*/
#line 22 "./sat-threshold-bb-equal.w"
;
if(r==0)/*8:*/
#line 157 "./sat-threshold-bb-equal.w"

{
for(i= 1;i<=n;i++){
xbar(n-2+i);
printf("\n");
}
}

/*:8*/
#line 23 "./sat-threshold-bb-equal.w"

else{
/*3:*/
#line 54 "./sat-threshold-bb-equal.w"

for(k= n+n-2;k>=n-1;k--)count[k]= 1;
for(;k>=0;k--)
count[k]= count[k+k+1]+count[k+k+2];
if(count[0]!=n)
fprintf(stderr,"I'm totally confused.\n");

/*:3*/
#line 25 "./sat-threshold-bb-equal.w"
;
for(i= n-2;i;i--){
/*4:*/
#line 68 "./sat-threshold-bb-equal.w"

{
t= count[i],tl= count[i+i+1],tr= count[i+i+2];
if(t> r+1)t= r+1;
if(tl> r)tl= r;
if(tr> r)tr= r;
for(jl= 0;jl<=tl;jl++)for(jr= 0;jr<=tr;jr++)
if((jl+jr<=t)&&(jl+jr> 0)){
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
#line 27 "./sat-threshold-bb-equal.w"
;
/*5:*/
#line 95 "./sat-threshold-bb-equal.w"

{
t= count[i],tl= count[i+i+1]+1,tr= count[i+i+2]+1;
if(t> r)t= r;
if(tl> r)tl= r;
if(tr> r)tr= r;
for(jl= 1;jl<=tl;jl++)for(jr= 1;jr<=tr;jr++)
if(jl+jr<=t+1){
if(jl<=count[i+i+1]){
if(i+i+1>=n-1)x(i+i+1);
else printf("B%d.%d",i+i+2,jl);
}
if(jr<=count[i+i+2]){
printf(" ");
if(i+i+2>=n-1)x(i+i+2);
else printf("B%d.%d",i+i+3,jr);
}
printf(" ~B%d.%d\n",i+1,jl+jr-1);
}
}


/*:5*/
#line 28 "./sat-threshold-bb-equal.w"
;
}
/*7:*/
#line 138 "./sat-threshold-bb-equal.w"

tl= count[1]+1,tr= count[2]+1;
if(tl> r)tl= r;
for(jl= 1;jl<=tl;jl++){
jr= r+1-jl;
if(jr<=tr){
if(jl<=count[1]){
if(1>=n-1)x(1);
else if(jl<=tl)printf("B2.%d",jl);
}
if(jr<tr){
printf(" ");
if(2>=n-1)x(2);
else if(jr<=tr)printf("B3.%d",jr);
}
printf("\n");
}
}

/*:7*/
#line 30 "./sat-threshold-bb-equal.w"
;
/*6:*/
#line 120 "./sat-threshold-bb-equal.w"

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

/*:6*/
#line 31 "./sat-threshold-bb-equal.w"
;
}
}

/*:1*/
