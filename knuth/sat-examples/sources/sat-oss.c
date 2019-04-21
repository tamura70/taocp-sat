#define maxmn '~'-'0'
#define bufsize 128 \

/*1:*/
#line 23 "./sat-oss.w"

#include <stdio.h> 
#include <stdlib.h> 
int m,n,t;
int w[maxmn][maxmn];
char buf[bufsize];
main(int argc,char*argv[]){
register int i,j,ii,jj,k,l;
/*2:*/
#line 37 "./sat-oss.w"

if(argc!=4||
sscanf(argv[1],"%d",&m)!=1||
sscanf(argv[2],"%d",&n)!=1||
sscanf(argv[3],"%d",&t)!=1){
fprintf(stderr,"Usage: %s m n t < w[m][n]\n",argv[0]);
exit(-1);
}
if(m> maxmn){
fprintf(stderr,"Sorry, m (%d) must not exceed %d!\n",m,maxmn);
exit(-2);
}
if(n> maxmn){
fprintf(stderr,"Sorry, n (%d) must not exceed %d!\n",n,maxmn);
exit(-3);
}

/*:2*/
#line 31 "./sat-oss.w"
;
/*3:*/
#line 56 "./sat-oss.w"

while(1){
i= getc(stdin);ungetc(i,stdin);
if(i!='~')break;
fgets(buf,bufsize,stdin);
printf("%s",
buf);
}
for(i= 0;i<m;i++){
for(j= 0;j<n;j++){
if(fscanf(stdin,"%d",&w[i][j])!=1){
fprintf(stderr,"Oops, I had trouble reading w%d%d!\n",i,j);
exit(-4);
}
if(w[i][j]<0||w[i][j]> t){
fprintf(stderr,"Oops, w%d%d should be between 0 and %d, not %d!\n",
i,j,t,w[i][j]);
exit(-5);
}
}
}
for(i= 0;i<m;i++){
for(k= 0,j= 0;j<n;j++)k+= w[i][j];
if(k> t){
fprintf(stderr,"Unsatisfiable (machine %d needs %d)!\n",i,k);
exit(-10);
}
}
for(j= 0;j<n;j++){
for(k= 0,i= 0;i<m;i++)k+= w[i][j];
if(k> t){
fprintf(stderr,"Unsatisfiable (job %d needs %d)!\n",j,k);
exit(-11);
}
}
printf("~ sat-oss %d %d %d\n",m,n,t);
for(i= 0;i<m;i++){
printf("~ ");
for(j= 0;j<n;j++)printf("%4d",w[i][j]);
printf("\n");
}

/*:3*/
#line 32 "./sat-oss.w"
;
/*4:*/
#line 102 "./sat-oss.w"

for(i= 0;i<m;i++)for(j= 0;j<n;j++)if(w[i][j])
for(l= 1;l<t-w[i][j];l++)
printf("~%c%c<%d %c%c<%d\n",'0'+i,'0'+j,l,'0'+i,'0'+j,l+1);

/*:4*/
#line 33 "./sat-oss.w"
;
/*5:*/
#line 107 "./sat-oss.w"

for(i= 0;i<m;i++)for(j= 0;j<n;j++)if(w[i][j]){
for(ii= 0;ii<m;ii++)for(jj= 0;jj<n;jj++)
if(((ii==i&&jj!=j)||(ii!=i&&jj==j))&&w[ii][jj]){
for(l= 0;l+w[i][j]<=t+1-w[ii][jj];l++){
if(i<ii||j<jj)printf("~!%c%c%c%c",'0'+i,'0'+j,'0'+ii,'0'+jj);
else printf("!%c%c%c%c",'0'+ii,'0'+jj,'0'+i,'0'+j);
if(l> 0)printf(" %c%c<%d",'0'+i,'0'+j,l);
if(l+w[i][j]<t+1-w[ii][jj])printf(" ~%c%c<%d",'0'+ii,'0'+jj,l+w[i][j]);
printf("\n");
}
}
}

/*:5*/
#line 34 "./sat-oss.w"
;
}

/*:1*/
