#define nmax 1000 \

#define x(k) printf("%d.%d", \
((k) -mn+1) /n,((k) -mn+1) % \
n)  \

/*1:*/
#line 25 "./sat-zarank.w"

#include <stdio.h> 
#include <stdlib.h> 
int m,n,r,p,q;
int count[2*nmax];
main(int argc,char*argv[]){
register int i,j,ii,jj,k,mn,t,tl,tr,jl,jr;
/*2:*/
#line 39 "./sat-zarank.w"

if(argc!=6||sscanf(argv[1],"%d",
&m)!=1
||sscanf(argv[2],"%d",
&n)!=1
||sscanf(argv[3],"%d",
&r)!=1
||sscanf(argv[4],"%d",
&p)!=1
||sscanf(argv[5],"%d",
&q)!=1){
fprintf(stderr,"Usage: %s m n r p q\n",
argv[0]);
exit(-1);
}
mn= m*n;
if(mn> nmax){
fprintf(stderr,"Sorry: mn is %d, and I'm set up for at most %d!\n",
mn,nmax);
exit(-2);
}
if(p> n){
fprintf(stderr,"Parameter p should be at most n (%d), not %d!\n",
n,p);
exit(-3);
}
if(q> m){
fprintf(stderr,"Parameter q should be at most m (%d), not %d!\n",
m,q);
exit(-4);
}
#line 18 "./sat-zarank-symm.ch"
if(m!=n){
fprintf(stderr,"In this version m must equal n!\n");
exit(-5);
}
printf("~ sat-zarank-symm %d %d %d %d %d\n",
m,n,r,p,q);
#line 72 "./sat-zarank.w"

/*:2*/
#line 32 "./sat-zarank.w"
;
/*4:*/
#line 86 "./sat-zarank.w"

for(i= 1;i<m;i++){
for(k= 1;k<=p;k++){
if(k!=p){
if(k!=1)printf("~R%d.%d",
i,k-1);
printf(" R%d.%d %d.%d\n",
i,k,i-1,k-1);
if(k!=1)printf("~R%d.%d",
i,k-1);
printf(" R%d.%d ~%d.%d\n",
i,k,i,k-1);
}
if(k!=1)printf("~R%d.%d",
i,k-1);
printf(" %d.%d ~%d.%d\n",
i-1,k-1,i,k-1);
}
}

/*:4*/
#line 33 "./sat-zarank.w"
;
/*5:*/
#line 106 "./sat-zarank.w"

for(i= 1;i<n;i++){
for(k= 1;k<=q;k++){
if(k!=q){
if(k!=1)printf("~C%d.%d",
k-1,i);
printf(" C%d.%d %d.%d\n",
k,i,k-1,i-1);
if(k!=1)printf("~C%d.%d",
k-1,i);
printf(" C%d.%d ~%d.%d\n",
k,i,k-1,i);
}
if(k!=1)printf("~C%d.%d",
k-1,i);
printf(" %d.%d ~%d.%d\n",
k-1,i-1,k-1,i);
}
}

/*:5*/
#line 34 "./sat-zarank.w"
;
#line 11 "./sat-zarank-symm.ch"
/*3:*/
#line 73 "./sat-zarank.w"

for(i= 0;i<m;i++)for(ii= i+1;ii<m;ii++)
for(j= 0;j<n;j++)for(jj= j+1;jj<n;jj++){
printf("~%d.%d ~%d.%d ~%d.%d ~%d.%d\n",
i,j,ii,j,i,jj,ii,jj);
}

/*:3*/
#line 11 "./sat-zarank-symm.ch"
;
/*10:*/
#line 28 "./sat-zarank-symm.ch"

for(i= 0;i<m;i++)for(j= 0;j<n;j++)if(i!=j)
printf("%d.%d ~%d.%d\n",
i,j,j,i);

/*:10*/
#line 12 "./sat-zarank-symm.ch"
;
#line 36 "./sat-zarank.w"
/*6:*/
#line 129 "./sat-zarank.w"

/*7:*/
#line 139 "./sat-zarank.w"

for(k= mn+mn-2;k>=mn-1;k--)count[k]= 1;
for(;k>=0;k--)
count[k]= count[k+k+1]+count[k+k+2];
if(count[0]!=mn)
fprintf(stderr,"I'm totally confused.\n");

/*:7*/
#line 130 "./sat-zarank.w"
;
r= mn-r;
for(i= mn-2;i;i--)/*8:*/
#line 155 "./sat-zarank.w"

{
t= count[i],tl= count[i+i+1],tr= count[i+i+2];
if(t> r+1)t= r+1;
if(tl> r)tl= r;
if(tr> r)tr= r;
for(jl= 0;jl<=tl;jl++)for(jr= 0;jr<=tr;jr++)
if((jl+jr<=t)&&(jl+jr)> 0){
if(jl){
if(i+i+1>=mn-1)x(i+i+1);
else printf("~B%d.%d",i+i+2,jl);
}
if(jr){
printf(" ");
if(i+i+2>=mn-1)x(i+i+2);
else printf("~B%d.%d",i+i+3,jr);
}
if(jl+jr<=r)printf(" B%d.%d\n",i+1,jl+jr);
else printf("\n");
}
}

/*:8*/
#line 132 "./sat-zarank.w"
;
/*9:*/
#line 180 "./sat-zarank.w"

tl= count[1],tr= count[2];
if(tl> r)tl= r;
for(jl= 1;jl<=tl;jl++){
jr= r+1-jl;
if(jr<=tr){
if(1>=mn-1)x(1);
else printf("~B2.%d",jl);
printf(" ");
if(2>=mn-1)x(2);
else printf("~B3.%d",jr);
printf("\n");
}
}

#line 28 "./sat-zarank-symm.ch"
/*:9*/
#line 133 "./sat-zarank.w"
;

/*:6*/
#line 36 "./sat-zarank.w"
;
}

/*:1*/
