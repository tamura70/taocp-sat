#define mmax 100
#define nmax 100
#define bufsize nmax+2 \

/*1:*/
#line 13 "./sat-tomography-prep.w"

#include <stdio.h> 
#include <stdlib.h> 
char rast[mmax][nmax];
char buf[nmax+2];
int m,n;
FILE*list_file;
main(int argc,char*argv[])
{
#line 12 "./sat-tomography-prep-2nd.ch"
register int d,j,k,jmax,kmax,t,tt;
#line 23 "./sat-tomography-prep.w"
/*2:*/
#line 29 "./sat-tomography-prep.w"

if(argc!=3||sscanf(argv[1],"%d",&m)!=1||sscanf(argv[2],"%d",&n)!=1){
fprintf(stderr,"Usage: %s m n < foo.dots > foo.tom\n",argv[0]);
exit(-1);
}

/*:2*/
#line 23 "./sat-tomography-prep.w"
;
/*3:*/
#line 35 "./sat-tomography-prep.w"

list_file= fopen("/tmp/list","w");
if(!list_file){
fprintf(stderr,"I can't open `/tmp/list' for writing!\n");
exit(-999);
}

/*:3*/
#line 24 "./sat-tomography-prep.w"
;
/*4:*/
#line 42 "./sat-tomography-prep.w"

kmax= 0;
for(j= 0;j<mmax;j++){
if(!fgets(buf,bufsize,stdin))break;
for(k= 0;k<nmax;k++){
if(buf[k]=='\n')break;
rast[j][k]= (buf[k]=='*');
if(rast[j][k])fprintf(list_file,"~%dx%d\n",
j+1,k+1);
if(k> kmax&&rast[j][k])kmax= k;
}
}
jmax= j-1;
fprintf(stderr,"OK, I've input an image with %d rows and %d columns.\n",
jmax+1,kmax+1);
if(m<=0||m> jmax+1){
fprintf(stderr,"So your m is out of range!\n"),
exit(-2);
}
if(n<=0||n> kmax+1){
fprintf(stderr,"So your n is out of range!\n"),
exit(-3);
}

#line 43 "./sat-tomography-prep-2nd.ch"
/*:4*/
#line 25 "./sat-tomography-prep.w"
;
/*5:*/
#line 43 "./sat-tomography-prep-2nd.ch"

for(j= 0;j<m;j++){
for(t= tt= 0,k= 0;k<n;k++)t+= rast[j][k],tt+= (k<n-1?rast[j][k]*rast[j][k+1]:0);
printf("r%d=%d,%d\n",
j+1,t,tt);
}
for(k= 0;k<n;k++){
for(t= tt= 0,j= 0;j<m;j++)t+= rast[j][k],tt+= (j<m-1?rast[j][k]*rast[j+1][k]:0);
printf("c%d=%d,%d\n",
k+1,t,tt);
}
for(d= 1;d<m+n;d++){
for(t= tt= 0,j= 0;j<m;j++){
k= d-1-j;
if(k>=0&&k<n)t+= rast[j][k],
tt+= (j<m-1&&k> 0?rast[j][k]*rast[j+1][k-1]:0);
}
printf("a%d=%d,%d\n",
d,t,tt);
}
for(d= 1;d<m+n;d++){
for(t= tt= 0,j= 0;j<m;j++){
k= j+n-d;
if(k>=0&&k<n)t+= rast[j][k],
tt+= (j<m-1&&k<n-1?rast[j][k]*rast[j+1][k+1]:0);
}
printf("b%d=%d,%d\n",
d,t,tt);
}
#line 93 "./sat-tomography-prep.w"

/*:5*/
#line 26 "./sat-tomography-prep.w"
;
}

/*:1*/
