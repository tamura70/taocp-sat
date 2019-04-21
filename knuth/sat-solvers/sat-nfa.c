#define badstate(k) ((k) <'!'||(k) >='~'||(k) =='0'||(k) =='1')  \

/*1:*/
#line 36 "./sat-nfa.w"

#include <stdio.h> 
#include <stdlib.h> 
int n;
char isinput[128],isoutput[128],isstate[128];
char istrans[128][2];
main(int argc,char*argv[]){
register int a,j,k,q;
/*2:*/
#line 55 "./sat-nfa.w"

if(argc<4||sscanf(argv[1],"%d",
&n)!=1){
fprintf(stderr,"Usage: %s n I O {qaq'}*\n",
argv[0]);
exit(-1);
}
for(j= 0;argv[2][j];j++){
k= argv[2][j];
if(badstate(k)){
fprintf(stderr,"Improper input state `%c'!\n",
k);
exit(-2);
}
isinput[k]= 1;
}
for(j= 0;argv[3][j];j++){
k= argv[3][j];
if(badstate(k)){
fprintf(stderr,"Improper input state `%c'!\n",
k);
exit(-3);
}
isoutput[k]= 1;
}
for(j= 4;j<argc;j++){
if(badstate(argv[j][0])||badstate(argv[j][2])||
argv[j][1]<'0'||argv[j][1]> '1'||argv[j][3]){
fprintf(stderr,"Improper transition `%s'!\n",
argv[j]);
exit(-4);
}
isstate[argv[j][0]]= 1;
isstate[argv[j][2]]= 1;
istrans[argv[j][2]][argv[j][1]-'0']= 1;
}
printf("~");
for(k= 0;k<argc;k++)printf(" %s",
argv[k]);
printf("\n");

/*:2*/
#line 44 "./sat-nfa.w"
;
for(k= 1;k<=n;k++){
/*3:*/
#line 96 "./sat-nfa.w"

for(q= '!';q<'~';q++)if(isstate[q]){
if(istrans[q][0]){
printf("~%c0%d ~%d\n",
q,k,k);
printf("~%c0%d %c%d\n",
q,k,q,k);
}
if(istrans[q][1]){
printf("~%c1%d %d\n",
q,k,k);
printf("~%c1%d %c%d\n",
q,k,q,k);
}
}

/*:3*/
#line 46 "./sat-nfa.w"
;
/*4:*/
#line 112 "./sat-nfa.w"

for(q= '!';q<'~';q++)if(isstate[q]){
printf("~%c%d",
q,k-1);
for(j= 4;j<argc;j++)if(argv[j][0]==q)
printf(" %c%c%d",
argv[j][2],argv[j][1],k);
printf("\n");
}

/*:4*/
#line 47 "./sat-nfa.w"
;
/*5:*/
#line 122 "./sat-nfa.w"

for(q= '!';q<'~';q++)if(isstate[q]){
printf("~%c%d",
q,k);
for(j= 4;j<argc;j++)if(argv[j][2]==q)
printf(" %c%c%d",
argv[j][2],argv[j][1],k);
printf("\n");
}

/*:5*/
#line 48 "./sat-nfa.w"
;
/*6:*/
#line 132 "./sat-nfa.w"

printf("%d",
k);
for(j= 4;j<argc;j++)if(argv[j][1]=='0')
printf(" %c0%d",
argv[j][2],k);
printf("\n");
printf("~%d",
k);
for(j= 4;j<argc;j++)if(argv[j][1]=='1')
printf(" %c1%d",
argv[j][2],k);
printf("\n");

/*:6*/
#line 49 "./sat-nfa.w"
;
/*7:*/
#line 146 "./sat-nfa.w"

for(q= '!';q<'~';q++)if(isstate[q]){
for(a= '0';a<'2';a++)if(istrans[q][a-'0']){
printf("~%c%c%d",
q,a,k);
for(j= 4;j<argc;j++)if(argv[j][2]==q&&argv[j][1]==a)
printf(" %c%d",
argv[j][0],k-1);
printf("\n");
}
}

/*:7*/
#line 50 "./sat-nfa.w"
;
}
/*8:*/
#line 158 "./sat-nfa.w"

for(q= '!';q<'~';q++)if(isstate[q]){
if(!isinput[q])printf("~%c0\n",
q);
if(!isoutput[q])printf("~%c%d\n",
q,n);
}

/*:8*/
#line 52 "./sat-nfa.w"
;
}

/*:1*/
