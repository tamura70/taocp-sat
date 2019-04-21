#define maxr 100 \

/*1:*/
#line 82 "./sat-arithprog.w"

#include <stdio.h> 
#include <stdlib.h> 
FILE*infile;
int table[maxr+1];
int t,n,r;
char buf[16];
main(int argc,char*argv[]){
register int b,d,i,j,k,p,q;
/*2:*/
#line 100 "./sat-arithprog.w"

if(argc!=4||sscanf(argv[1],"%d",&t)!=1||
sscanf(argv[2],"%d",&n)!=1||
sscanf(argv[3],"%d",&r)!=1){
fprintf(stderr,"Usage: %s t n r\n",argv[0]);
exit(-1);
}
if(r> maxr){
fprintf(stderr,"Sorry, r (%d) should not exceed %d!\n",r,maxr);
exit(-2);
}
if(n>=256){
fprintf(stderr,"Sorry, n (%d) must not exceed 255!\n",n);
exit(-3);
}

/*:2*/
#line 91 "./sat-arithprog.w"
;
/*3:*/
#line 116 "./sat-arithprog.w"

sprintf(buf,"free%d.dat",t);
infile= fopen(buf,"r");
if(!infile){
fprintf(stderr,"I can't open file `%s' for reading!\n",buf);
exit(-5);
}
for(j= 1;j<r;j++){
if(fscanf(infile,"%d",&table[j])!=1){
fprintf(stderr,"I couldn't read item %d in file `%s'!\n",j,buf);
exit(-6);
}
}
table[r]= n;

/*:3*/
#line 92 "./sat-arithprog.w"
;
printf("~ sat-arithprog %d %d %d\n",t,n,r);
/*4:*/
#line 131 "./sat-arithprog.w"

for(d= 1;1+(t-1)*d<=n;d++){
for(i= 1;i+(t-1)*d<=n;i++){
for(j= 0;j<t;j++)printf(" ~x%d",i+j*d);
printf("\n");
}
}

/*:4*/
#line 94 "./sat-arithprog.w"
;
/*5:*/
#line 139 "./sat-arithprog.w"

for(j= 1;j<n-r;j++)for(k= 1;k<=r;k++)
printf("~%dS%d %dS%d\n",j,k,j+1,k);
for(j= 1;j<=n-r;j++)for(k= 1;k<r;k++)
printf("%dS%d ~%dS%d\n",j,k,j,k+1);
for(j= 1;j<=n-r;j++)for(k= 0;k<=r;k++){
printf("~x%d",j+k);
if(k> 0)printf(" ~%dS%d",j,k);
if(k<r)printf(" %dS%d",j,k+1);
printf("\n");
}
for(j= 0;j<=n-r;j++)for(k= 1;k<=r;k++){
printf("x%d",j+k);
if(j> 0)printf(" %dS%d",j,k);
if(j<n-r)printf(" ~%dS%d",j+1,k);
printf("\n");
}

/*:5*/
#line 95 "./sat-arithprog.w"
;
/*6:*/
#line 157 "./sat-arithprog.w"

for(q= 2;q<r;q++)if(table[q+1]> table[q]+1){
p= table[q+1]-1;
for(b= 0;b<=n-r+1-p+q;b++)for(k= q+1;k<=r;k++){
if(b+p-q<=n-r)printf("~%dS%d",b+p-q,k);
if(b> 0)printf(" %dS%d",b,k-q);
printf("\n");
}
}

/*:6*/
#line 96 "./sat-arithprog.w"
;
/*7:*/
#line 174 "./sat-arithprog.w"

if(r&1){
j= (n-r+1)>>1,k= (r+1)>>1;
printf("~%dS%d\n",j,k);
}else if(!(n&1)){
j= (n-r)>>1,k= r>>1;
printf("%dS%d\n",j+1,k);
}


/*:7*/
#line 97 "./sat-arithprog.w"
;
}

/*:1*/
