/*1:*/
#line 11 "./sat-erdos-disc.w"

#include <stdio.h> 
#include <stdlib.h> 
int n;
/*3:*/
#line 65 "./sat-erdos-disc.w"

void generate(int d,int n){
register int i,j,k,t;
for(t= 1;2*t+3<=n;t++)/*4:*/
#line 72 "./sat-erdos-disc.w"

{
printf("~%dB%d %dA%d\n",
d,t,d,t+1);
printf("~%dC%d %dB%d\n",
d,t,d,t+1);
printf("%dB%d ~%dC%d\n",
d,t,d,t);
printf("%dA%d ~%dB%d\n",
d,t+1,d,t+1);
}

/*:4*/
#line 68 "./sat-erdos-disc.w"
;
for(t= 1;2*t+1<=n;t++)/*5:*/
#line 84 "./sat-erdos-disc.w"

{
if(t> 1){
printf("~X%d %dA%d\n",
d*(t+t-2),d,t);
printf("X%d ~%dC%d\n",
d*(t+t-2),d,t-1);
printf("~X%d ~%dA%d %dB%d\n",
d*(t+t-1),d,t,d,t);
printf("X%d %dC%d ~%dB%d\n",
d*(t+t-1),d,t-1,d,t);
}else{
printf("~X%d %dB%d\n",
d,d,1);
printf("X%d ~%dB%d\n",
d,d,1);
}
printf("~X%d ~%dB%d %dC%d\n",
d*(t+t),d,t,d,t);
printf("X%d %dB%d ~%dA%d\n",
d*(t+t),d,t,d,t+1);
printf("~X%d ~%dC%d\n",
d*(t+t+1),d,t);
printf("X%d %dA%d\n",
d*(t+t+1),d,t+1);
}

/*:5*/
#line 69 "./sat-erdos-disc.w"
;
}

/*:3*/
#line 15 "./sat-erdos-disc.w"

main(int argc,char*argv[]){
register int d;
/*2:*/
#line 25 "./sat-erdos-disc.w"

if(argc!=2||sscanf(argv[1],"%d",&n)!=1){
fprintf(stderr,"Usage: %s n\n",argv[0]);
exit(-1);
}

/*:2*/
#line 18 "./sat-erdos-disc.w"
;
printf("~ sat-erdos-disc %d\n",n);
printf("X%d\n",
n<720?360:720);
for(d= 1;3*d<=n;d++)generate(d,n/d);
}

/*:1*/
