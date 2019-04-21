#define maxr 20 \

#define xi (x&is) 
#define xj (x&js) 
#define yi (y&is) 
#define yj (y&js)  \

/*1:*/
#line 18 "./sat-mintime-sort.w"

#include <stdio.h> 
#include <stdlib.h> 
int n,tt,ii,jj;
int mask[maxr+maxr],m[16];
int leaf[32];
char needed[1<<16];
main(int argc,char*argv[]){
register int i,is,j,js,k,l,r,t,x,y,z;
/*2:*/
#line 33 "./sat-mintime-sort.w"

if(argc==1||(argc&1)==0||argc> maxr+maxr+3||
sscanf(argv[1],"%d",
&n)!=1||
sscanf(argv[2],"%d",
&tt)!=1){
fprintf(stderr,"Usage: %s n t i1 j1 ... ir jr\n",
argv[0]);
exit(-1);
}
if(n<3||n> 15){
fprintf(stderr,"Sorry, n must be between 3 and 15!\n");
exit(-2);
}
printf("~ sat-mintime-sort %d %d",
n,tt);
for(j= 3;argv[j];j++)printf(" %s",
argv[j]);
printf("\n");

/*:2*/
#line 27 "./sat-mintime-sort.w"
;
/*3:*/
#line 59 "./sat-mintime-sort.w"

for(t= 1;t<=tt;t++)for(k= 1;k<=n;k++){
for(i= n-1,j= 1;j<=n;j++){
if(j<k)leaf[i++]= (j<<4)+k;
else if(j> k)leaf[i++]= (k<<4)+j;
}
for(j= n-2;j;j--){
if(j+j>=n-1)printf("~%xC%d",
leaf[j+j],t);
else printf("~%x%xB%d",
k,j+j,t);
if(j+j+1>=n-1)printf(" ~%xC%d\n",
leaf[j+j+1],t);
else printf(" ~%x%xB%d\n",
k,j+j+1,t);
if(j+j>=n-1)printf("~%xC%d %x%xB%d\n",
leaf[j+j],t,k,j,t);
else printf("~%x%xB%d %x%xB%d\n",
k,j+j,t,k,j,t);
if(j+j+1>=n-1)printf("~%xC%d %x%xB%d\n",
leaf[j+j+1],t,k,j,t);
else printf("~%x%xB%d %x%xB%d\n",
k,j+j+1,t,k,j,t);
printf("~%x%xB%d",
k,j,t);
if(j+j>=n-1)printf(" %xC%d",
leaf[j+j],t);
else printf(" %x%xB%d",
k,j+j,t);
if(j+j+1>=n-1)printf(" %xC%d\n",
leaf[j+j+1],t);
else printf(" %x%xB%d\n",
k,j+j+1,t);
}
}

/*:3*/
#line 28 "./sat-mintime-sort.w"
;
/*4:*/
#line 95 "./sat-mintime-sort.w"

/*5:*/
#line 107 "./sat-mintime-sort.w"

for(i= 0;argv[i+i+3];i++){
if(sscanf(argv[i+i+3],"%d",
&ii)!=1||
sscanf(argv[i+i+4],"%d",
&jj)!=1||
ii<1|ii> n|jj<=ii|jj> n){
fprintf(stderr,"Invalid comparator [%s:%s"
"]\n",argv[i+i+3],argv[i+i+4]);
exit(-3);
}
mask[i]= ((1<<n)>>ii)|((1<<n)>>jj);
}
r= i;

/*:5*//*7:*/
#line 156 "./sat-mintime-sort.w"

for(i= 0;i<=n;i++)m[i]= (1<<(n-i))-1;

/*:7*/
#line 96 "./sat-mintime-sort.w"
;
/*6:*/
#line 125 "./sat-mintime-sort.w"

for(x= 2;x<(1<<n);x++){
for(y= x,i= 0;i<r;i++){
t= mask[i]&-mask[i];
if((y&mask[i])==mask[i]-t)y^= mask[i];
}
if(y&(y+1))needed[y]= 1;
}

/*:6*/
#line 97 "./sat-mintime-sort.w"
;
for(x= 2;x<(1<<n);x++)if(needed[x]){
for(t= 1;t<=tt;t++){
for(i= 1,is= 1<<(n-1);is;i++,is>>= 1)for(j= i+1,js= is>>1;js;j++,js>>= 1)
/*8:*/
#line 159 "./sat-mintime-sort.w"

{
for(y= x;z= y&(y+1);y-= z>>1);
if(x<=m[i]||(t==1&&xi)||(t==tt&&!yi));
else{
printf("~%x%xC%d",
i,j,t);
if(t!=tt)printf(" ~%04x%xV%d",
x,i,t);
if(t!=1)printf(" %04x%xV%d",
x,i,t-1);
printf("\n");
}
if(x<=m[i]||((x+1)&m[j-1])==0||(t==1&&xj)||(t==tt&&!yi));
else{
printf("~%x%xC%d",
i,j,t);
if(t!=tt)printf(" ~%04x%xV%d",
x,i,t);
if(t!=1)printf(" %04x%xV%d",
x,j,t-1);
printf("\n");
}
if(x<=m[i]||(t==1&&(!xi||!xj))||(t==tt&&yi));
else{
printf("~%x%xC%d",
i,j,t);
if(t!=tt)printf(" %04x%xV%d",
x,i,t);
if(t!=1){
printf(" ~%04x%xV%d",
x,i,t-1);
if((x+1)&m[j-1])printf(" ~%04x%xV%d",
x,j,t-1);
}
printf("\n");
}
if(x<=m[i]||((x+1)&m[j-1])==0||(t==1&&!xi)||(t==tt&&yj));
else{
printf("~%x%xC%d",
i,j,t);
if(t!=tt)printf(" %04x%xV%d",
x,j,t);
if(t!=1)printf(" ~%04x%xV%d",
x,i,t-1);
printf("\n");
}
if(((x+1)&m[j-1])==0||(t==1&&!xj)||(t==tt&&yj));
else{
printf("~%x%xC%d",
i,j,t);
if(t!=tt)printf(" %04x%xV%d",
x,j,t);
if(t!=1)printf(" ~%04x%xV%d",
x,j,t-1);
printf("\n");
}
if(((x+1)&m[j-1])==0||(t==1&&(xi||xj))||(t==tt&&!yj));
else{
printf("~%x%xC%d",
i,j,t);
if(t!=tt)printf(" ~%04x%xV%d",
x,j,t);
if(t!=1){
if(x> m[i])printf(" %04x%xV%d",x,i,t-1);
printf(" %04x%xV%d",
x,j,t-1);
}
printf("\n");
}
}

/*:8*/
#line 101 "./sat-mintime-sort.w"
;
for(i= 1,is= 1<<(n-1);is;i++,is>>= 1)
/*9:*/
#line 233 "./sat-mintime-sort.w"

{
if(x<=m[i]||((x+1)&m[i-1])==0||(t==1&&xi)||(t==tt&&!yi));
else{
printf("%x1B%d",
i,t);
if(t!=tt)printf(" ~%04x%xV%d",
x,i,t);
if(t!=1)printf(" %04x%xV%d",
x,i,t-1);
printf("\n");
}
if(x<=m[i]||((x+1)&m[i-1])==0||(t==1&&!xi)||(t==tt&&yi));
else{
printf("%x1B%d",
i,t);
if(t!=tt)printf(" %04x%xV%d",
x,i,t);
if(t!=1)printf(" ~%04x%xV%d",
x,i,t-1);
printf("\n");
}
}

/*:9*/
#line 103 "./sat-mintime-sort.w"
;
}
}

/*:4*/
#line 29 "./sat-mintime-sort.w"
;
/*10:*/
#line 259 "./sat-mintime-sort.w"

for(i= 0;i<r;i++){
for(j= i+1;j<r;j++){
if(mask[i]&mask[j])break;
}
if(j==r){
for(j= 1,t= 1<<(n-1);t;j++,t>>= 1){
if(mask[i]&t)break;
}
for(k= j+1,t>>= 1;t;k++,t>>= 1){
if(mask[i]&t)break;
}
printf("~%x%xC1\n",
j,k);
}
}

/*:10*/
#line 30 "./sat-mintime-sort.w"
;
}

/*:1*/
