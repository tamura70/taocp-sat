#define maxn 100
#define O "%" \

/*1:*/
#line 50 "./sat-synth.w"

#include <stdio.h> 
#include <stdlib.h> 
char buf[maxn+4];
#line 4 "./sat-synth-trunc-kluj.ch"
int K,N,cutoff;
int perm_swap[]= {0,1,2,0,2,1,0,2,0,1,2,0,2,1,0,2,0,1,2,0,2,1,0};
int perm[]= {1,2,3,4};
int dat[4][21];
#line 55 "./sat-synth.w"
main(int argc,char*argv[]){
#line 12 "./sat-synth-trunc-kluj.ch"
register int i,j,k,t,count;
#line 57 "./sat-synth.w"
/*2:*/
#line 66 "./sat-synth.w"

#line 30 "./sat-synth-trunc-kluj.ch"
if(argc!=4||sscanf(argv[1],""O"d",&N)!=1||
sscanf(argv[2],""O"d",&K)!=1||
sscanf(argv[3],""O"d",&cutoff)!=1){
fprintf(stderr,"Usage: "O"s N K cutoff\n",argv[0]);
#line 70 "./sat-synth.w"
exit(-1);
}
if(N> maxn){
fprintf(stderr,
"That N ("O"d) is too big for me, I'm set up for at most "O"d!\n",N,maxn);
exit(-2);
}

/*:2*/
#line 57 "./sat-synth.w"
;
#line 17 "./sat-synth-trunc-kluj.ch"
printf("~ sat-synth-trunc-kluj %d %d %d\n",N,K,cutoff);
/*6:*/
#line 38 "./sat-synth-trunc-kluj.ch"

dat[0][2]= dat[0][3]= dat[0][10]= -1;
dat[1][6]= dat[1][10]= dat[1][12]= -1;
dat[2][8]= 1,dat[2][13]= dat[2][15]= -1;
dat[3][10]= 1,dat[3][8]= dat[3][12]= -1;
for(i= 0;;i++){
for(j= 0;j<4;j++)for(k= 1;k<=20;k++){
if(dat[j][k]> 0)
printf(" ~"O"d+"O"d "O"d-"O"d",perm[j],k,perm[j],k);
else if(dat[j][k]<0)
printf(" "O"d+"O"d ~"O"d-"O"d",perm[j],k,perm[j],k);
else printf(" "O"d+"O"d "O"d-"O"d",perm[j],k,perm[j],k);
}
printf("\n");
if(i==23)break;
j= perm_swap[i];
k= perm[j],perm[j]= perm[j+1],perm[j+1]= k;
}

/*:6*/
#line 18 "./sat-synth-trunc-kluj.ch"
;
#line 59 "./sat-synth.w"
t= 0;
#line 23 "./sat-synth-trunc-kluj.ch"
for(count= 0;count<cutoff;count++){
#line 61 "./sat-synth.w"
if(!fgets(buf,N+4,stdin))break;
/*3:*/
#line 81 "./sat-synth.w"

if(buf[N]!=':'||buf[N+1]<'0'||buf[N+1]> '1'||buf[N+2]!='\n'||buf[N+3])
fprintf(stderr,"bad input line `"O"s' is ignored!\n",buf);
else{
for(k= 0;k<N;k++)if(buf[k]<'0'||buf[k]> '1')break;
if(k<N)fprintf(stderr,"nonbinary data `"O"s' is ignored!\n",buf);
else if(buf[N+1]=='0')/*4:*/
#line 91 "./sat-synth.w"

{
for(i= 1;i<=K;i++){
for(j= 1;j<=N;j++)
printf(" "O"d"O"c"O"d",i,buf[j-1]=='0'?'+':'-',j);
printf("\n");
}
}

/*:4*/
#line 87 "./sat-synth.w"

else/*5:*/
#line 100 "./sat-synth.w"

{
t++;
for(i= 1;i<=K;i++)printf(" "O"d."O"d",i,t);
printf("\n");
for(i= 1;i<=K;i++)for(j= 1;j<=N;j++)
printf("~"O"d."O"d ~"O"d"O"c"O"d\n",i,t,i,buf[j-1]=='0'?'+':'-',j);
}


#line 38 "./sat-synth-trunc-kluj.ch"
/*:5*/
#line 88 "./sat-synth.w"
;
}

/*:3*/
#line 62 "./sat-synth.w"
;
}
}

/*:1*/
