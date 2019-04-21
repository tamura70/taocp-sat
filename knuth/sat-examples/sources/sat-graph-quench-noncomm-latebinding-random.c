#define nmax 256 \

#define stamp u.I \

/*1:*/
#line 36 "./sat-graph-quench.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"
#line 22 "./sat-graph-quench-noncomm-latebinding-random.ch"
#include <string.h> 
#include "gb_flip.h"
char*cardname[52]= {
"Ac","2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc",
"Ad","2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd",
"Ah","2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh",
"As","2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks"};
int seed;
main(int argc,char*argv[]){
register char*tt;
#line 42 "./sat-graph-quench.w"
register int i,j,k,t,n;
register Arc*a;
register Graph*g;
register Vertex*v,*w;
/*2:*/
#line 58 "./sat-graph-quench-noncomm-latebinding-random.ch"

if(argc!=2||sscanf(argv[1],"%d",&seed)!=1){
fprintf(stderr,"Usage: %s seed\n",argv[0]);
exit(-1);
}
gb_init_rand(seed);
n= 18;
for(j= 0;j<n;j++){
i= j+gb_unif_rand(52-j);
tt= cardname[i],cardname[i]= cardname[j],cardname[j]= tt;
}
printf("~ sat-graph-quench-noncomm-latebinding-random %d\n",seed);
printf("~");
for(j= 0;j<n;j++)printf(" %s",cardname[j]);
printf("\n");
#line 70 "./sat-graph-quench.w"

/*:2*/
#line 46 "./sat-graph-quench.w"
;
/*3:*/
#line 85 "./sat-graph-quench-noncomm-latebinding-random.ch"

for(i= 0;i<n;i++)for(j= i+1;j<n;j++){
if(cardname[i][0]==cardname[j][0])continue;
if(cardname[i][1]==cardname[j][1])continue;
printf("~00%02x%02x\n",
i,j);
}
#line 87 "./sat-graph-quench.w"

/*:3*/
#line 47 "./sat-graph-quench.w"
;
/*4:*/
#line 88 "./sat-graph-quench.w"

for(t= 0;t<n-1;t++){
for(k= 1;k<n-t;k++)printf(" %02xQ%02x",
t,k-1);
for(k= 1;k<n-t-2;k++)printf(" %02xS%02x",
t,k-1);
printf("\n");
}

/*:4*/
#line 48 "./sat-graph-quench.w"
;
#line 36 "./sat-graph-quench-noncomm-latebinding-random.ch"
/*5:*/
#line 97 "./sat-graph-quench.w"

for(t= 0;t<n-1;t++){
for(k= 1;k<n-t;k++)printf("~%02xQ%02x %02x%02x%02x\n",
t,k-1,t,k-1,k);
for(k= 1;k<n-t-2;k++)printf("~%02xS%02x %02x%02x%02x\n",
t,k-1,t,k-1,k+2);
}

/*:5*/
#line 36 "./sat-graph-quench-noncomm-latebinding-random.ch"
;
/*7:*/
#line 111 "./sat-graph-quench-noncomm-latebinding-random.ch"

for(t= 0;t<=n-3;t++){
for(i= 0;i<=n-t-2;i++)for(j= i+2;j<=n-t-2;j++)
printf("~%02xQ%02x ~%02xQ%02x\n",
t,j,t+1,i);
for(i= 0;i<=n-t-2;i++)for(j= i+2;j<=n-t-4;j++)
printf("~%02xS%02x ~%02xQ%02x\n",
t,j,t+1,i);
for(i= 0;i<=n-t-4;i++)for(j= i+4;j<=n-t-4;j++)
printf("~%02xS%02x ~%02xS%02x\n",
t,j,t+1,i);
for(i= 0;i<=n-t-4;i++)for(j= i+3;j<=n-t-2;j++)
printf("~%02xQ%02x ~%02xS%02x\n",
t,j,t+1,i);
for(j= 1;j<=n-t-2;j++)
printf("~%02xQ%02x ~%02xQ%02x ~%02x%02x%02x\n",
t,j,t+1,j-1,t,j-1,j);
for(j= 1;j<=n-t-4;j++)
printf("~%02xQ%02x ~%02xS%02x ~%02x%02x%02x\n",
t,j,t+1,j-1,t,j,j+3);
}

/*:7*/
#line 37 "./sat-graph-quench-noncomm-latebinding-random.ch"
;
#line 50 "./sat-graph-quench.w"
/*6:*/
#line 105 "./sat-graph-quench.w"

for(t= 0;t<n-1;t++){
for(k= 1;k<n-t;k++)
for(i= 1;i<n-t;i++)for(j= i+1;j<n-t;j++)
printf("~%02xQ%02x ~%02x%02x%02x %02x%02x%02x\n",
t,k-1,t+1,i-1,j-1,t,i<k?i-1:i,j<k?j-1:j);
for(k= 1;k<n-t-2;k++)
for(i= 1;i<n-t;i++)for(j= i+1;j<n-t;j++){
register iprev= (i==k?i+2:i<k+3?i-1:i),
jprev= (j==k?j+2:j<k+3?j-1:j);
printf("~%02xS%02x ~%02x%02x%02x %02x%02x%02x\n",
t,k-1,t+1,i-1,j-1,t,iprev<jprev?iprev:jprev,iprev<jprev?jprev:iprev);
}
}

#line 96 "./sat-graph-quench-noncomm-latebinding-random.ch"
/*:6*/
#line 50 "./sat-graph-quench.w"
;
}

#line 58 "./sat-graph-quench-noncomm-latebinding-random.ch"
/*:1*/
