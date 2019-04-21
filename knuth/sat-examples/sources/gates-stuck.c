#define stuck_at_one(v) (Vertex*) ((unsigned long long) (v) +1) 
#define how_stuck(v) (int) ((unsigned long long) (v) &1) 
#define clean(v) ((Vertex*) ((unsigned long long) (v) &-2) )  \

#define stuck0 u.I
#define stuck1 v.I \

#define size w.I \

/*1:*/
#line 36 "./gates-stuck.w"

#include "gb_graph.h"
#include "gb_gates.h"
#include "gb_flip.h"
#include "gb_save.h"
unsigned long long**bits;
Vertex**faults;
int seed;
double bias;
unsigned long long thresh= 2147483648>>1;
FILE*pat_file,*fault_file;
main(int argc,char*argv[]){
register int i,j,k,n,r,s;
register unsigned long long udefault,vdefault;
register Vertex*u,*v;
register Arc*a;
register Graph*g;
int faults_left,faults_found,tolerance;
/*2:*/
#line 76 "./gates-stuck.w"

if(argc<3||argc> 6||sscanf(argv[2],"%d",&seed)!=1){
fprintf(stderr,"Usage: %s gates.gb seed [bias] [patternfile] [faultfile]\n",
argv[0]);
exit(-1);
}
g= restore_graph(argv[1]);
if(!g){
fprintf(stderr,"I can't restore the graph `%s'!\n",
argv[1]);
exit(-2);
}
if(argc> 3){
if(sscanf(argv[3],"%lf",&bias)!=1||bias<=0.0||bias>=1.0){
fprintf(stderr,
"The bias should be strictly between 0.0 and 1.0 (default 0.5)!\n");
exit(-8);
}
thresh= bias*2147483648.0;
if(argc> 4){
pat_file= fopen(argv[4],"w");
if(!pat_file){
fprintf(stderr,"I can't open the pattern file `%s' for writing!\n",
argv[4]);
exit(-3);
}
if(argc> 5){
fault_file= fopen(argv[5],"w");
if(!fault_file){
fprintf(stderr,"I can't open the fault file `%s' for writing!\n",
argv[5]);
exit(-4);
}
}
}
}
gb_init_rand(seed);

/*:2*/
#line 54 "./gates-stuck.w"
;
n= g->n;
/*3:*/
#line 114 "./gates-stuck.w"

bits= (unsigned long long**)malloc((n+1)*sizeof(unsigned long long*));
if(!bits){
fprintf(stderr,"I can't allocate the bits array!\n");
exit(-5);
}
k= 1+(n>>5);
if(sizeof(unsigned long long)!=8){
fprintf(stderr,"Sorry, I wrote this code assuming 64-bit words!\n");
exit(-6);
}
for(j= 0;j<n;j++){
bits[j]= (unsigned long long*)malloc(k*sizeof(unsigned long long));
if(!bits[j]){
fprintf(stderr,"I can't allocate the array bits[%d]!\n",
j);
exit(-7);
}
}

/*:3*//*4:*/
#line 144 "./gates-stuck.w"

faults= (Vertex**)malloc((n+n+1)*sizeof(Vertex*));
if(!faults){
fprintf(stderr,"I can't allocate the faults array!\n");
exit(-8);
}

/*:4*/
#line 56 "./gates-stuck.w"
;
/*5:*/
#line 158 "./gates-stuck.w"

for(v= g->vertices;v<g->vertices+n&&v->typ=='I';v++)v->val= 0;
for(;v<g->vertices+n&&v->typ=='L';v++){
v->val= 0;
a= gb_virgin_arc();
a->next= g->outs;
a->tip= v->alt;
g->outs= a;
}
for(;v<g->vertices+n;v++)v->val= 0;
for(k= 0,a= g->outs;a;a= a->next)
a->tip->val= ++k;

/*:5*/
#line 57 "./gates-stuck.w"
;
/*6:*/
#line 177 "./gates-stuck.w"

faults_left= 0;
for(v= g->vertices;v<g->vertices+n;v++)
v->stuck0= v->stuck1= 1,faults_left+= 2;

/*:6*/
#line 58 "./gates-stuck.w"
;
fprintf(stderr,"(considering %d possible single-stuck-at faults)\n",
faults_left);
tolerance= seed/1000;
while(faults_left){
faults_found= 0;
/*7:*/
#line 205 "./gates-stuck.w"

for(s= j= 0;j<n;j++){
v= g->vertices+j;
/*8:*/
#line 225 "./gates-stuck.w"

switch(v->typ){
case'I':case'L':/*9:*/
#line 238 "./gates-stuck.w"

vdefault= -(gb_next_rand()<thresh);
for(k= 0;k<=s>>6;k++)bits[j][k]= vdefault;

/*:9*/
#line 227 "./gates-stuck.w"
;break;
case'&':/*12:*/
#line 275 "./gates-stuck.w"

vdefault= -1;
for(k= 0;k<=s>>6;k++)bits[j][k]= vdefault;
for(a= v->arcs;a;a= a->next){
u= a->tip,i= u-g->vertices;
udefault= -(bits[i][0]&1),r= u->size;
for(k= 0;k<=r>>6;k++)bits[j][k]&= bits[i][k];
if(udefault==0){
vdefault= 0;
for(;k<=s>>6;k++)bits[j][k]= 0;
}
}

/*:12*/
#line 228 "./gates-stuck.w"
;break;
case'|':/*13:*/
#line 288 "./gates-stuck.w"

vdefault= 0;
for(k= 0;k<=s>>6;k++)bits[j][k]= vdefault;
for(a= v->arcs;a;a= a->next){
u= a->tip,i= u-g->vertices;
udefault= -(bits[i][0]&1),r= u->size;
for(k= 0;k<=r>>6;k++)bits[j][k]|= bits[i][k];
if(udefault){
vdefault= -1;
for(;k<=s>>6;k++)bits[j][k]= -1;
}
}

/*:13*/
#line 229 "./gates-stuck.w"
;break;
case'^':/*14:*/
#line 301 "./gates-stuck.w"

vdefault= 0;
for(k= 0;k<=s>>6;k++)bits[j][k]= vdefault;
for(a= v->arcs;a;a= a->next){
u= a->tip,i= u-g->vertices;
udefault= -(bits[i][0]&1),r= u->size;
for(k= 0;k<=r>>6;k++)bits[j][k]^= bits[i][k];
if(udefault){
vdefault^= udefault;
for(;k<=s>>6;k++)bits[j][k]^= -1;
}
}

/*:14*/
#line 230 "./gates-stuck.w"
;break;
case'~':/*10:*/
#line 242 "./gates-stuck.w"

if(!v->arcs||v->arcs->next){
fprintf(stderr,"Inverter %s (%d) should have exactly one operand!\n",
v->name,j);
exit(-11);
}
u= v->arcs->tip;
i= u-g->vertices;
udefault= -(bits[i][0]&1),r= u->size;
vdefault= ~udefault;
for(k= 0;k<=r>>6;k++)bits[j][k]= ~bits[i][k];
for(;k<=s>>6;k++)bits[j][k]= vdefault;

/*:10*/
#line 231 "./gates-stuck.w"
;break;
case'F':/*11:*/
#line 258 "./gates-stuck.w"

if(!v->arcs||v->arcs->next){
fprintf(stderr,"Fanout branch %s (%d) should have exactly one operand!\n",
v->name,j);
exit(-11);
}
u= v->arcs->tip;
i= u-g->vertices;
udefault= -(bits[i][0]&1),r= u->size;
vdefault= udefault;
for(k= 0;k<=r>>6;k++)bits[j][k]= bits[i][k];
for(;k<=s>>6;k++)bits[j][k]= vdefault;

/*:11*/
#line 232 "./gates-stuck.w"
;break;
default:fprintf(stderr,"Vertex %s (%d) has unknown gate type `%c'!\n",
v->name,j,(char)v->typ);
exit(-10);
}

/*:8*/
#line 208 "./gates-stuck.w"
;
if(v->stuck0){
s++;
faults[s]= v;
if((s&0x3f)==0)bits[j][s>>6]= vdefault;
bits[j][s>>6]&= ~(1ULL<<(s&0x3f));
}
if(v->stuck1){
s++;
faults[s]= stuck_at_one(v);
if((s&0x3f)==0)bits[j][s>>6]= vdefault;
bits[j][s>>6]|= 1ULL<<(s&0x3f);
}
v->size= s;
if(v->val)/*15:*/
#line 317 "./gates-stuck.w"

{
for(k= 0;k<=s>>6;k++)if(bits[j][k]^vdefault){
udefault= bits[j][k]^vdefault;
for(i= 0;i<64;i++)if(udefault&(1ULL<<i)){
u= faults[(k<<6)+i];
if(how_stuck(u)){
u= clean(u);
if(u->stuck1){
faults_found++,u->stuck1= 0;
if(fault_file)fprintf(fault_file," 1%s",
u->name);
}
}else{
if(u->stuck0){
faults_found++,u->stuck0= 0;
if(fault_file)fprintf(fault_file," 0%s",
u->name);
}
}
}
}
}

/*:15*/
#line 222 "./gates-stuck.w"
;
}

/*:7*/
#line 64 "./gates-stuck.w"
;
faults_left-= faults_found;
fprintf(stderr,"(found %d; %d left)\n",
faults_found,faults_left);
if(faults_found){
tolerance= seed/1000;
if(pat_file)/*17:*/
#line 362 "./gates-stuck.w"

{
for(j= 0;j<n;j++){
v= g->vertices+j;
if(v->typ=='I'||v->typ=='L')
fprintf(pat_file,"%c",
(char)('0'+(bits[j][0]&1)));
}
fprintf(pat_file,"->");
for(a= g->outs;a;a= a->next){
v= a->tip;
fprintf(pat_file,"%c",
(char)('0'+(bits[v-g->vertices][0]&1)));
}
fprintf(pat_file,"\n");
if(fault_file)fprintf(fault_file,"\n");
}

/*:17*/
#line 70 "./gates-stuck.w"
;
}else if(--tolerance<0)break;
}
/*16:*/
#line 344 "./gates-stuck.w"

for(k= 1;k<=faults_left;k++){
v= clean(faults[k]);
printf(" %c%s",
how_stuck(faults[k])?'1':'0',v->name);
}
printf("\n");
if(pat_file){
fprintf(stderr,"Test patterns written on file `%s'",
argv[4]);
if(fault_file)fprintf(stderr,"; covered faults written on file `%s'.\n",
argv[5]);
else fprintf(stderr,".\n");
}

/*:16*/
#line 73 "./gates-stuck.w"
;
}

/*:1*/
