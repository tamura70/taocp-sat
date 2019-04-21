/*1:*/
#line 17 "./sat-newlangford.w"

#include <stdio.h> 
#include <stdlib.h> 
int n;
main(int argc,char*argv[]){
register int i,j,k,nn;
/*2:*/
#line 29 "./sat-newlangford.w"

if(argc!=2||sscanf(argv[1],"%d",&n)!=1){
fprintf(stderr,"Usage: %s n\n",argv[0]);
exit(-1);
}
nn= n+n;

/*:2*/
#line 23 "./sat-newlangford.w"
;
/*3:*/
#line 36 "./sat-newlangford.w"

for(i= 1;i<=nn;i++){
printf("~%dy%d\n",i,0);
printf("~%dz%d\n",0,i);
printf("%dy%d\n",i,nn);
printf("%dz%d\n",nn,i);
}
for(i= 1;i<=nn;i++)for(j= 1;j<=nn;j++){
printf("~%dy%d %dy%d\n",i,j-1,i,j);
printf("~%dz%d %dz%d\n",i-1,j,i,j);
}

/*:3*/
#line 24 "./sat-newlangford.w"
;
/*4:*/
#line 51 "./sat-newlangford.w"

for(i= 1;i<=nn;i++)for(j= 1;j<=nn;j++){
printf("~%dy%d %dz%d ~%dz%d\n",i,j-1,i-1,j,i,j);
printf("%dy%d %dz%d ~%dz%d\n",i,j,i-1,j,i,j);
printf("%dy%d ~%dy%d ~%dz%d\n",i,j-1,i,j,i-1,j);
printf("%dy%d ~%dy%d %dz%d\n",i,j-1,i,j,i,j);
}

/*:4*/
#line 25 "./sat-newlangford.w"
;
/*5:*/
#line 59 "./sat-newlangford.w"

for(i= 1;i<=n;i++){
printf("%dy%d\n",i,nn-1-i);
printf("~%dy%d\n",i+n,i+1);
}
for(i= 1;i<=n;i++){
for(j= 1;j<=nn-1-i;j++){
printf("%dy%d ~%dy%d ~%dy%d\n",i,j-1,i,j,i+n,i+j);
printf("%dy%d ~%dy%d %dy%d\n",i,j-1,i,j,i+n,i+j+1);
}
for(j= i+2;j<=nn;j++){
printf("%dy%d ~%dy%d ~%dy%d\n",i+n,j-1,i+n,j,i,j-i-2);
printf("%dy%d ~%dy%d %dy%d\n",i+n,j-1,i+n,j,i,j-i-1);
}
}

/*:5*/
#line 26 "./sat-newlangford.w"
;
}

/*:1*/
