/*1:*/
#line 9 "./sat-waerden.w"

#include <stdio.h> 
#include <stdlib.h> 
int k,l,n;
main(int argc,char*argv[]){
register int i,j,d;
/*2:*/
#line 20 "./sat-waerden.w"

if(argc!=4||sscanf(argv[1],"%d",&k)!=1||
sscanf(argv[2],"%d",&l)!=1||
sscanf(argv[3],"%d",&n)!=1){
fprintf(stderr,"Usage: %s k l n\n",argv[0]);
exit(-1);
}
printf("~ sat-waerden %d %d %d\n",k,l,n);

/*:2*/
#line 15 "./sat-waerden.w"
;
/*3:*/
#line 29 "./sat-waerden.w"

for(d= 1;1+(k-1)*d<=n;d++){
for(i= 1;i+(k-1)*d<=n;i++){
for(j= 0;j<k;j++)printf(" %d",i+j*d);
printf("\n");
}
}

/*:3*/
#line 16 "./sat-waerden.w"
;
/*4:*/
#line 37 "./sat-waerden.w"

for(d= 1;1+(l-1)*d<=n;d++){
for(i= 1;i+(l-1)*d<=n;i++){
for(j= 0;j<l;j++)printf(" ~%d",i+j*d);
printf("\n");
}
}

/*:4*/
#line 17 "./sat-waerden.w"
;
}

/*:1*/
