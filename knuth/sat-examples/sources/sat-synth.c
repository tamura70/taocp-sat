#define maxn 100
#define O "%" \

/*1:*/
#line 50 "./sat-synth.w"

#include <stdio.h> 
#include <stdlib.h> 
char buf[maxn+4];
int K,N;
main(int argc,char*argv[]){
register int i,j,k,t;
/*2:*/
#line 66 "./sat-synth.w"

if(argc!=3||sscanf(argv[1],""O"d",&N)!=1||
sscanf(argv[2],""O"d",&K)!=1){
fprintf(stderr,"Usage: "O"s N K\n",argv[0]);
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
printf("~ sat-synth %d %d\n",N,K);
t= 0;
while(1){
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
