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
#line 54 "./sat-erdos-disc-res.ch"

{
if(t> 1){
printf("~X%d ~%dB%d %dB%d\n",
d*(t+t+1),d,t,d,t+1);
printf("~X%d ~%dB%d %dB%d\n",
d*(t+t),d,t,d,t+1);
printf("X%d %dB%d ~%dB%d\n",
d*(t+t+1),d,t,d,t+1);
printf("X%d %dB%d ~%dB%d\n",
d*(t+t),d,t,d,t+1);
}else{
printf("~X%d ~X%d %dB%d\n",
d*3,d,d,t+1);
printf("~X%d ~X%d %dB%d\n",
d*2,d,d,t+1);
printf("X%d X%d ~%dB%d\n",
d*3,d,d,t+1);
printf("X%d X%d ~%dB%d\n",
d*2,d,d,t+1);
}
}

/*:4*/
#line 68 "./sat-erdos-disc.w"
;
for(t= 1;2*t+1<=n;t++)/*5:*/
#line 77 "./sat-erdos-disc-res.ch"

{
if(t> 1){
printf("X%d X%d %dB%d\n",
d*(t+t),d*(t+t+1),d,t);
if(2*t+3<=n)printf("X%d X%d ~%dB%d\n",
d*(t+t),d*(t+t+1),d,t+1);
printf("~X%d ~X%d ~%dB%d\n",
d*(t+t),d*(t+t+1),d,t);
if(2*t+3<=n)printf("~X%d ~X%d %dB%d\n",
d*(t+t),d*(t+t+1),d,t+1);
}else{
printf("X%d X%d X%d\n",
d*(t+t),d*(t+t+1),d);
if(5<=n)printf("X%d X%d ~%dB%d\n",
d*(t+t),d*(t+t+1),d,2);
printf("~X%d ~X%d ~X%d\n",
d*(t+t),d*(t+t+1),d);
if(5<=n)printf("~X%d ~X%d %dB%d\n",
d*(t+t),d*(t+t+1),d,2);
}
}
#line 110 "./sat-erdos-disc.w"

/*:5*/
#line 69 "./sat-erdos-disc.w"
;
}

#line 54 "./sat-erdos-disc-res.ch"
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
#line 4 "./sat-erdos-disc-res.ch"
printf("~ sat-erdos-disc-res %d\n",n);
#line 20 "./sat-erdos-disc.w"
printf("X%d\n",
n<720?360:720);
for(d= 1;3*d<=n;d++)generate(d,n/d);
}

/*:1*/
