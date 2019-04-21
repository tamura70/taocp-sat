#define maxsteps 100
#define bufsize 1024 \

#define abrt(m,t) {fprintf(stderr,"Oops, %s!\n> %s\n",m,buf) ;exit(t) ;} \

#define printprevA() if(j) printf("%03d_A%d",t+1,i-1) ; \
else printf("~%03d%.4s",t+1,state[astep[k-1]].name) ; \

#define printprevB() if(j) printf("%03d_B%d",t+1,i-1) ; \
else printf("~%03d%.4s",t+1,state[bstep[k-1]].name) ; \

#define tprime (t+1)  \

/*2:*/
#line 71 "./sat-mutex.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
/*4:*/
#line 104 "./sat-mutex.w"

typedef struct state_struct{
char name[4],lab[4],elab[4];
char var[2];
char val;
char crit;
}step;

/*:4*/
#line 75 "./sat-mutex.w"
;
step state[maxsteps];
char vars[maxsteps][2];
int astep[maxsteps],bstep[maxsteps];
int r;
char buf[bufsize];
main(int argc,char*argv[]){
register int i,j,k,m,n,t,ma,mb;
/*3:*/
#line 91 "./sat-mutex.w"

if(argc!=2||sscanf(argv[1],"%d",&r)!=1){
fprintf(stderr,"Usage: %s r < foo.dat\n",argv[0]);
exit(-1);
}
if(r<=0){
fprintf(stderr,"Parameter r must be positive!\n");
exit(-2);
}
printf("~ sat-mutex %d\n",r);

/*:3*/
#line 83 "./sat-mutex.w"
;
/*5:*/
#line 117 "./sat-mutex.w"

for(m= n= ma= mb= 0;;){
if(!fgets(buf,bufsize,stdin))break;
if(buf[0]=='~')printf("%s",buf);
else{
char*curp= buf;
if(m>=maxsteps){
fprintf(stderr,"Recompile me -- I only have room for %d steps!\n",
maxsteps);
exit(-666);
}
/*6:*/
#line 146 "./sat-mutex.w"

for(j= 0;*curp&&*curp!=' '&&*curp!='\n';j++,curp++)
if(j<4)state[m].name[j]= *curp;
if(j> 4)abrt("the name is too long",-10);
if(state[m].name[0]<'A'||state[m].name[0]> 'B')
abrt("the step name must begin with A or B",-11);
for(j= 0;j<m;j++)if(strncmp(state[j].name,state[m].name,4)==0)
abrt("that name has already been used",-12);
if(state[m].name[0]=='A')astep[ma++]= m;
else bstep[mb++]= m;
if(*curp++!=' ')abrt("step is incomplete",-13);

/*:6*/
#line 128 "./sat-mutex.w"
;
if(strncmp(curp,"maybe ",6)==0)/*7:*/
#line 158 "./sat-mutex.w"

{
curp+= 5;
/*9:*/
#line 173 "./sat-mutex.w"

if(strncmp(curp," goto ",6)!=0)abrt("missing goto",-16);
curp+= 6;
for(j= 0;*curp&&*curp!=' '&&*curp!='\n';j++,curp++)
if(j<4)state[m].lab[j]= *curp;
if(j> 4)abrt("the label is too long",-17);

/*:9*/
#line 161 "./sat-mutex.w"
;
if(*curp!='\n')abrt("maybe step ends badly",-14);
}

/*:7*/
#line 129 "./sat-mutex.w"

else if(strncmp(curp,"critical ",9)==0)/*8:*/
#line 165 "./sat-mutex.w"

{
curp+= 8;
state[m].crit= 1;
/*9:*/
#line 173 "./sat-mutex.w"

if(strncmp(curp," goto ",6)!=0)abrt("missing goto",-16);
curp+= 6;
for(j= 0;*curp&&*curp!=' '&&*curp!='\n';j++,curp++)
if(j<4)state[m].lab[j]= *curp;
if(j> 4)abrt("the label is too long",-17);

/*:9*/
#line 169 "./sat-mutex.w"
;
if(*curp!='\n')abrt("critical step ends badly",-15);
}

/*:8*/
#line 130 "./sat-mutex.w"

else if(strncmp(curp,"if ",3)==0)/*10:*/
#line 180 "./sat-mutex.w"

{
curp+= 3;
/*11:*/
#line 191 "./sat-mutex.w"

for(j= 0;*curp&&*curp!='='&&*curp!='\n';j++,curp++)
if(j<2)state[m].var[j]= vars[n][j]= *curp;
if(j> 2)abrt("the variable name is too long",-20);
if(state[m].var[0]<'a'||state[m].var[0]> 'z')
abrt("a variable name must begin with a lowercase letter",-21);
for(j= 0;j<n;j++)if(strncmp(vars[j],state[m].var,2)==0)break;
if(j==n)n++;
else vars[n][1]= 0;

/*:11*/
#line 183 "./sat-mutex.w"
;
if(*curp++!='=')abrt("missing `=' in an if step",-18);
/*12:*/
#line 201 "./sat-mutex.w"

if(*curp<'0'||*curp> '1')abrt("the value must be 0 or 1",-22);
state[m].val= *curp++-'0';

/*:12*/
#line 185 "./sat-mutex.w"
;
/*9:*/
#line 173 "./sat-mutex.w"

if(strncmp(curp," goto ",6)!=0)abrt("missing goto",-16);
curp+= 6;
for(j= 0;*curp&&*curp!=' '&&*curp!='\n';j++,curp++)
if(j<4)state[m].lab[j]= *curp;
if(j> 4)abrt("the label is too long",-17);

/*:9*/
#line 186 "./sat-mutex.w"
;
/*13:*/
#line 205 "./sat-mutex.w"

if(strncmp(curp," else ",6)!=0)abrt("missing else",-23);
curp+= 6;
for(j= 0;*curp&&*curp!='\n';j++,curp++)if(j<4)state[m].elab[j]= *curp;
if(j> 4)abrt("the else label is too long",-24);

/*:13*/
#line 187 "./sat-mutex.w"
;
if(*curp!='\n')abrt("that if step ends badly",-19);
}

/*:10*/
#line 131 "./sat-mutex.w"

else/*14:*/
#line 211 "./sat-mutex.w"

{
/*11:*/
#line 191 "./sat-mutex.w"

for(j= 0;*curp&&*curp!='='&&*curp!='\n';j++,curp++)
if(j<2)state[m].var[j]= vars[n][j]= *curp;
if(j> 2)abrt("the variable name is too long",-20);
if(state[m].var[0]<'a'||state[m].var[0]> 'z')
abrt("a variable name must begin with a lowercase letter",-21);
for(j= 0;j<n;j++)if(strncmp(vars[j],state[m].var,2)==0)break;
if(j==n)n++;
else vars[n][1]= 0;

/*:11*/
#line 213 "./sat-mutex.w"
;
if(*curp++!='=')abrt("missing `=' in an assignment step",-25);
/*12:*/
#line 201 "./sat-mutex.w"

if(*curp<'0'||*curp> '1')abrt("the value must be 0 or 1",-22);
state[m].val= *curp++-'0';

/*:12*/
#line 215 "./sat-mutex.w"
;
/*9:*/
#line 173 "./sat-mutex.w"

if(strncmp(curp," goto ",6)!=0)abrt("missing goto",-16);
curp+= 6;
for(j= 0;*curp&&*curp!=' '&&*curp!='\n';j++,curp++)
if(j<4)state[m].lab[j]= *curp;
if(j> 4)abrt("the label is too long",-17);

/*:9*/
#line 216 "./sat-mutex.w"
;
if(*curp!='\n')abrt("assignment step ends badly",-26);
}

/*:14*/
#line 132 "./sat-mutex.w"
;
m++;
}
}
/*15:*/
#line 220 "./sat-mutex.w"

if(ma==0){
fprintf(stderr,"There are no steps for process A!\n");
exit(-99);
}
if(mb==0){
fprintf(stderr,"There are no steps for process B!\n");
exit(-98);
}
for(k= t= 0;k<m;k++){
if(state[k].lab[0]){
for(j= 0;j<m;j++)if(strncmp(state[j].name,state[k].lab,4)==0)break;
if(j==m){
fprintf(stderr,"Missing step %.4s!\n",state[k].lab);
t++;
}
}
if(state[k].elab[0]){
for(j= 0;j<m;j++)if(strncmp(state[j].name,state[k].elab,4)==0)break;
if(j==m){
fprintf(stderr,"Missing step %.4s!\n",state[k].elab);
t++;
}
}
}
if(t)exit(-30);

/*:15*/
#line 136 "./sat-mutex.w"
;
if(state[astep[0]].crit+state[bstep[0]].crit> 1){
fprintf(stderr,"Both processes are initially in critical sections!\n");
exit(-555);
}
fprintf(stderr,"(%d+%d steps with %d shared variables successfully input)\n",
ma,mb,n);

/*:5*/
#line 84 "./sat-mutex.w"
;
/*16:*/
#line 263 "./sat-mutex.w"

{
for(j= 0;j<n;j++)printf("~000%.2s\n",vars[j]);
printf("000%.4s\n",state[astep[0]].name);
for(j= 1;j<ma;j++)printf("~000%.4s\n",state[astep[j]].name);
printf("000%.4s\n",state[bstep[0]].name);
for(j= 1;j<mb;j++)printf("~000%.4s\n",state[bstep[j]].name);
}

/*:16*/
#line 85 "./sat-mutex.w"
;
for(t= 0;t<r;t++)
/*17:*/
#line 301 "./sat-mutex.w"

{
/*18:*/
#line 316 "./sat-mutex.w"

k= ma;
if(k> 1){
i= j= 0;
if(k==2)printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[astep[0]].name,t+1,state[astep[1]].name);
while(k> 4){
printprevA();printf(" ~%03d%.4s\n",
t+1,state[astep[k-2]].name);
printprevA();printf(" ~%03d%.4s\n",
t+1,state[astep[k-3]].name);
printprevA();printf(" ~%03d_A%d\n",
t+1,i);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[astep[k-2]].name,t+1,state[astep[k-3]].name);
printf("~%03d%.4s ~%03d_A%d\n",
t+1,state[astep[k-2]].name,t+1,i);
printf("~%03d%.4s ~%03d_A%d\n",
t+1,state[astep[k-3]].name,t+1,i);
i++,j= 1,k-= 2;
}
printprevA();printf(" ~%03d%.4s\n",
t+1,state[astep[k-2]].name);
printprevA();printf(" ~%03d%.4s\n",
t+1,state[astep[k-3]].name);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[astep[k-2]].name,t+1,state[astep[k-3]].name);
if(k> 3){
printprevA();printf(" ~%03d%.4s\n",
t+1,state[astep[k-4]].name);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[astep[k-2]].name,t+1,state[astep[k-4]].name);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[astep[k-3]].name,t+1,state[astep[k-4]].name);
}
}

/*:18*/
#line 303 "./sat-mutex.w"
;
/*19:*/
#line 356 "./sat-mutex.w"

k= mb;
if(k> 1){
i= j= 0;
if(k==2)printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[bstep[0]].name,t+1,state[bstep[1]].name);
while(k> 4){
printprevB();printf(" ~%03d%.4s\n",
t+1,state[bstep[k-2]].name);
printprevB();printf(" ~%03d%.4s\n",
t+1,state[bstep[k-3]].name);
printprevB();printf(" ~%03d_B%d\n",
t+1,i);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[bstep[k-2]].name,t+1,state[bstep[k-3]].name);
printf("~%03d%.4s ~%03d_B%d\n",
t+1,state[bstep[k-2]].name,t+1,i);
printf("~%03d%.4s ~%03d_B%d\n",
t+1,state[bstep[k-3]].name,t+1,i);
i++,j= 1,k-= 2;
}
printprevB();printf(" ~%03d%.4s\n",
t+1,state[bstep[k-2]].name);
printprevB();printf(" ~%03d%.4s\n",
t+1,state[bstep[k-3]].name);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[bstep[k-2]].name,t+1,state[bstep[k-3]].name);
if(k> 3){
printprevB();printf(" ~%03d%.4s\n",
t+1,state[bstep[k-4]].name);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[bstep[k-2]].name,t+1,state[bstep[k-4]].name);
printf("~%03d%.4s ~%03d%.4s\n",
t+1,state[bstep[k-3]].name,t+1,state[bstep[k-4]].name);
}
}

/*:19*/
#line 304 "./sat-mutex.w"
;
/*20:*/
#line 395 "./sat-mutex.w"

for(k= 0;k<ma;k++){
printf("%03d@ ~%03d%.4s %03d%.4s\n",
t,t,state[astep[k]].name,tprime,state[astep[k]].name);
if(state[astep[k]].var[0]==0){
if(state[astep[k]].crit==0)
printf("~%03d@ ~%03d%.4s %03d%.4s %03d%.4s\n",
t,t,state[astep[k]].name,
tprime,state[astep[k]].name,tprime,state[astep[k]].lab);
else printf("~%03d@ ~%03d%.4s %03d%.4s\n",
t,t,state[astep[k]].name,
tprime,state[astep[k]].lab);
}else if(state[astep[k]].elab[0]==0){
printf("~%03d@ ~%03d%.4s %03d%.4s\n",
t,t,state[astep[k]].name,tprime,state[astep[k]].lab);
}else/*21:*/
#line 413 "./sat-mutex.w"

{
printf("~%03d@ ~%03d%.4s",
t,t,state[astep[k]].name);
printf(" %s%03d%.2s %03d%.4s\n",
state[astep[k]].val?"~":"",t,state[astep[k]].var,
tprime,state[astep[k]].lab);
printf("~%03d@ ~%03d%.4s",
t,t,state[astep[k]].name);
printf(" %s%03d%.2s %03d%.4s\n",
state[astep[k]].val?"":"~",t,state[astep[k]].var,
tprime,state[astep[k]].elab);
}

/*:21*/
#line 410 "./sat-mutex.w"
;
}

/*:20*/
#line 305 "./sat-mutex.w"
;
/*22:*/
#line 427 "./sat-mutex.w"

for(k= 0;k<mb;k++){
printf("~%03d@ ~%03d%.4s %03d%.4s\n",
t,t,state[bstep[k]].name,tprime,state[bstep[k]].name);
if(state[bstep[k]].var[0]==0){
if(state[bstep[k]].crit==0)
printf("%03d@ ~%03d%.4s %03d%.4s %03d%.4s\n",
t,t,state[bstep[k]].name,
tprime,state[bstep[k]].name,tprime,state[bstep[k]].lab);
else printf("%03d@ ~%03d%.4s %03d%.4s\n",
t,t,state[bstep[k]].name,
tprime,state[bstep[k]].lab);
}else if(state[bstep[k]].elab[0]==0){
printf("%03d@ ~%03d%.4s %03d%.4s\n",
t,t,state[bstep[k]].name,tprime,state[bstep[k]].lab);
}else/*23:*/
#line 445 "./sat-mutex.w"

{
printf("%03d@ ~%03d%.4s",
t,t,state[bstep[k]].name);
printf(" %s%03d%.2s %03d%.4s\n",
state[bstep[k]].val?"~":"",t,state[bstep[k]].var,
tprime,state[bstep[k]].lab);
printf("%03d@ ~%03d%.4s",
t,t,state[bstep[k]].name);
printf(" %s%03d%.2s %03d%.4s\n",
state[bstep[k]].val?"":"~",t,state[bstep[k]].var,
tprime,state[bstep[k]].elab);
}

/*:23*/
#line 442 "./sat-mutex.w"
;
}

/*:22*/
#line 306 "./sat-mutex.w"
;
/*24:*/
#line 459 "./sat-mutex.w"

for(k= 0;k<n;k++){

for(j= 0;j<m;j++)
if(strncmp(state[j].var,vars[k],2)==0&&state[j].elab[0]==0)
printf("%s%03d@ ~%03d%.4s %s%03d%.2s\n",
state[j].name[0]=='A'?"~":"",t,t,state[j].name,
state[j].val==0?"~":"",tprime,state[j].var);

printf("~%03d@ %03d%.2s",
t,t,vars[k]);
for(j= 0;j<m;j++)
if(strncmp(state[j].var,vars[k],2)==0&&state[j].elab[0]==0
&&state[j].name[0]=='A')
printf(" %03d%.4s",
t,state[j].name);
printf(" ~%03d%.2s\n",
tprime,vars[k]);
printf("%03d@ %03d%.2s",
t,t,vars[k]);
for(j= 0;j<m;j++)
if(strncmp(state[j].var,vars[k],2)==0&&state[j].elab[0]==0
&&state[j].name[0]=='B')
printf(" %03d%.4s",
t,state[j].name);
printf(" ~%03d%.2s\n",
tprime,vars[k]);
printf("~%03d@ ~%03d%.2s",
t,t,vars[k]);
for(j= 0;j<m;j++)
if(strncmp(state[j].var,vars[k],2)==0&&state[j].elab[0]==0
&&state[j].name[0]=='A')
printf(" %03d%.4s",
t,state[j].name);
printf(" %03d%.2s\n",
tprime,vars[k]);
printf("%03d@ ~%03d%.2s",
t,t,vars[k]);
for(j= 0;j<m;j++)
if(strncmp(state[j].var,vars[k],2)==0&&state[j].elab[0]==0
&&state[j].name[0]=='B')
printf(" %03d%.4s",
t,state[j].name);
printf(" %03d%.2s\n",
tprime,vars[k]);
}

/*:24*/
#line 307 "./sat-mutex.w"
;
}

/*:17*/
#line 87 "./sat-mutex.w"
;
/*25:*/
#line 508 "./sat-mutex.w"

for(i= j= 0;j<ma;j++)if(state[astep[j]].crit){
for(k= 0;k<mb;k++)if(state[bstep[k]].crit){
printf("~C%d %03d%.4s\n",
i,r,state[astep[j]].name);
printf("~C%d %03d%.4s\n",
i,r,state[bstep[k]].name);
i++;
}
}
for(j= 0;j<i;j++)
printf(" C%d",
j);
printf("\n");

/*:25*/
#line 88 "./sat-mutex.w"
;
}

/*:2*/
